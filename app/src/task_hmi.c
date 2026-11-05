/**
 * @file  task_hmi.c
 * @brief MODULE 3 - TODO: DEV 3 hien thuc. Xem app/inc/task_hmi.h
 */
#include "task_hmi.h"
#include "app_cfg.h"
#include "app_ipc.h"
#include "joystick.h"
#include "hal_gpio.h"
#include "hal_pwm.h"
#include "hal_uart.h"
#include "bsp.h"

static TaskHandle_t s_hTask = NULL;

/* KHUNG VONG LAP (Dev 3 dien vao):
 *
 * static void prvHmiTask(void *pv)
 * {
 *     joystick_calibrate();          // nguoi choi khong cham joystick luc nay
 *     TickType_t last = xTaskGetTickCount();
 *
 *     for (;;) {
 *         joy_state_t j;
 *         joystick_read(&j);
 *         if (j.moved) {
 *             app_ipc_post_input(IN_MOVE, j.dx, j.dy);
 *         }
 *
 *         // nut bam da duoc ISR day vao g_xBtnSem
 *         // chay mot buoc cua trinh phat nhac (doi not neu den luc)
 *         // moi 1 giay: in perf_stat_t ra UART
 *         // nuoi watchdog
 *
 *         vTaskDelayUntil(&last, pdMS_TO_TICKS(HMI_PERIOD_MS));
 *     }
 * }
 *
 * ISR NUT BAM - QUY TAC AN TOAN:
 *   void EXTI15_10_IRQHandler(void) {
 *       BaseType_t woken = pdFALSE;
 *       // xoa co EXTI->PR bang cach GHI 1
 *       // chong doi: bo qua neu cach lan truoc duoi 200ms
 *       app_ipc_post_input(...) KHONG dung duoc trong ISR!
 *       // phai dung xQueueSendFromISR hoac xSemaphoreGiveFromISR
 *       portYIELD_FROM_ISR(woken);
 *   }
 *
 * BAY: trong ISR chi duoc goi ham co duoi ...FromISR(). Goi ham thuong
 *      se lam hong hang doi va treo he thong mot cach ngau nhien,
 *      rat kho tim ra.
 *
 * THU TU LAM:
 *   B1. In raw ADC hai truc ra UART. Xoay joystick thay so chay.
 *   B2. Hieu chuan + vung chet. Tha tay ra 0,0 on dinh.
 *   B3. Nut bam qua EXTI, chong doi.
 *   B4. PWM phat ba not Do Mi Sol.
 *   B5. Watchdog + __WFI() trong idle hook + do dong.
 */

void task_hmi_hw_init(void)
{
    /* TODO */
}

void task_hmi_play_sfx(sfx_id_t id)
{
    (void) id;   /* TODO */
}

BaseType_t task_hmi_create(void)
{
    (void) s_hTask;
    return pdFAIL;   /* TODO */
}
