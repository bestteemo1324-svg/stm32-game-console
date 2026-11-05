/**
 * @file  main.c
 * @brief He thong do hoa thoi gian thuc - may choi game cam tay.
 * @owner LEADER. Cac Dev KHONG commit truc tiep vao file nay.
 *        Can them gi thi de nghi trong PR, Leader sua.
 *
 *   [TASK_HMI] --queue--> [TASK_GAME] --semaphore--> [TASK_RENDER]
 *    joystick              the gioi                   TFT + OLED
 *    nut bam               va cham                    qua DMA
 *    am thanh              may trang thai
 */
#include "FreeRTOS.h"
#include "task.h"

#include "bsp.h"
#include "hal_gpio.h"
#include "hal_uart.h"
#include "hal_adc.h"

#include "app_cfg.h"
#include "app_ipc.h"
#include "task_render.h"
#include "task_game.h"
#include "task_hmi.h"

#include <stdio.h>

/** @brief Nhay LED vinh vien khi khoi tao that bai. */
static void prv_fatal(const char *reason)
{
    hal_uart_puts(reason);
    hal_uart_puts("\r\n");
    for (;;) {
        hal_gpio_toggle(PIN_LED_PORT, PIN_LED_PIN);
        bsp_delay_ms_blocking(100U);
    }
}

int main(void)
{
    /* 1. Phan cung co ban */
    bsp_system_init();
    hal_gpio_init_all();
    hal_uart_init(UART_BAUDRATE);
    hal_adc_init();

    hal_uart_puts("\r\n=====================================\r\n");
    hal_uart_puts(" MAY CHOI GAME CAM TAY - v0.1.0\r\n");
    hal_uart_puts(" STM32F103C8T6 + FreeRTOS + TFT\r\n");
    hal_uart_puts("=====================================\r\n");

    /* 2. IPC - PHAI truoc khi tao task */
    if (!app_ipc_init()) {
        prv_fatal("FATAL: khong du heap cho IPC");
    }

    /* 3. Phan cung cua tung module */
    task_hmi_hw_init();
    if (!task_render_hw_init()) {
        hal_uart_puts("WARN : man hinh chua san sang\r\n");
    }

    /* 4. Tao task */
    if (task_hmi_create()    != pdPASS) { prv_fatal("FATAL: tao TASK_HMI loi");    }
    if (task_game_create()   != pdPASS) { prv_fatal("FATAL: tao TASK_GAME loi");   }
    if (task_render_create() != pdPASS) { prv_fatal("FATAL: tao TASK_RENDER loi"); }

    {
        char buf[48];
        (void) snprintf(buf, sizeof(buf), "HEAP con lai: %u byte",
                        (unsigned) xPortGetFreeHeapSize());
        hal_uart_log(buf);
    }

    /* 5. Chay */
    vTaskStartScheduler();

    prv_fatal("FATAL: scheduler tra ve - thieu heap");
    return 0;
}

/* ==================== Hook bat buoc cua FreeRTOS ==================== */

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void) xTask;
    taskDISABLE_INTERRUPTS();
    hal_uart_puts("\r\n!!! STACK OVERFLOW: ");
    hal_uart_puts(pcTaskName);
    hal_uart_puts(" !!!\r\n");
    for (;;) { }
}

void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    hal_uart_puts("\r\n!!! MALLOC FAILED !!!\r\n");
    for (;;) { }
}

/**
 * @brief Chay khi khong task nao san sang.
 * @note  DAY LA CHO TIET KIEM DIEN. O 30 FPS, DMA ganh phan truyen nen
 *        CPU ranh khoang 70% thoi gian. __WFI() cho CPU ngu den ngat ke tiep.
 *        Do dong truoc va sau khi bat USE_LOW_POWER_IDLE de lay so lieu.
 */
void vApplicationIdleHook(void)
{
#if (USE_LOW_POWER_IDLE == 1)
    __WFI();
#endif
}
