/**
 * @file  app_cfg.h
 * @brief Bang tai nguyen RTOS va tham so game - THONG NHAT TOAN NHOM.
 * @owner LEADER. Doi so o day la doi lap lich cua ca ba nguoi.
 */
#ifndef APP_CFG_H
#define APP_CFG_H

#include "FreeRTOS.h"

/* ============ DO UU TIEN TASK ============
 * Rate Monotonic: chu ky ngan hon -> uu tien cao hon.
 * RENDER thap nhat vi phan nang do DMA lam, CPU chi ve framebuffer.
 */
#define TASK_HMI_PRIO       (tskIDLE_PRIORITY + 3U)
#define TASK_GAME_PRIO      (tskIDLE_PRIORITY + 2U)
#define TASK_RENDER_PRIO    (tskIDLE_PRIORITY + 1U)

/* ============ STACK (word = 4 byte) ============ */
#define TASK_HMI_STACK      (configMINIMAL_STACK_SIZE + 96U)
#define TASK_GAME_STACK     (configMINIMAL_STACK_SIZE + 192U)
#define TASK_RENDER_STACK   (configMINIMAL_STACK_SIZE + 160U)

/* ============ CHU KY ============ */
#define HMI_PERIOD_MS       20U   /**< 50 Hz doc joystick       */
#define GAME_TICK_MS        20U   /**< 50 Hz cap nhat the gioi  */
#define TARGET_FPS          30U

/* ============ HANG DOI ============ */
#define Q_INPUT_LEN         8U

/* ============ MAN HINH TFT ST7735 ============ */
#define TFT_W               128U
#define TFT_H               160U
#define TFT_BAND_H          8U    /**< So dong moi dai. Doi so nay la doi RAM! */
#define TFT_BAND_PIXELS     (TFT_W * TFT_BAND_H)
#define TFT_BAND_BYTES      (TFT_BAND_PIXELS * 2U)   /* 2048 byte / dai */
#define TFT_BAND_COUNT      (TFT_H / TFT_BAND_H)     /* 20 dai / khung  */

/* ============ MAN HINH OLED ============ */
#define OLED_W              128U
#define OLED_H              64U
#define OLED_PAGES          8U

/* ============ GAME ============
 * Toa do dang Q12.4 (1 pixel = 16 don vi) de chuyen dong muot.
 */
#define FIXED_SHIFT         4
#define TO_FIXED(px)        ((int16_t) ((px) << FIXED_SHIFT))
#define TO_PIXEL(fx)        ((int16_t) ((fx) >> FIXED_SHIFT))

#define MAX_ENEMIES         12U
#define MAX_BULLETS         6U
#define MAX_EGGS            6U

#define PLAYER_SPEED        24    /**< Q12.4 moi tick */
#define BULLET_SPEED        48
#define FIRE_COOLDOWN_TICK  8U
#define TOTAL_WAVES         3U    /**< Ban rut gon: 3 dot roi thang */

/* ============ JOYSTICK ============ */
#define JOY_CENTER          2048U  /**< ADC luc tha tay (do lai tren board) */
#define JOY_DEADZONE        300U

/* ============ UART ============ */
#define UART_BAUDRATE       115200U

/* ============ UU TIEN NGAT ============
 * BAT BUOC >= configMAX_SYSCALL_INTERRUPT_PRIORITY (= 5) voi moi ISR
 * co goi API ...FromISR(). So cang LON = uu tien cang THAP.
 */
#define IRQ_PRIO_BUTTON     7U
#define IRQ_PRIO_DMA_SPI    6U

/* ============ WATCHDOG ============ */
#define USE_IWDG            1
#define IWDG_TIMEOUT_MS     2000U

/* ============ TIET KIEM DIEN ============
 * Bat len de idle hook goi __WFI(). Do dong truoc/sau de lay so lieu bao cao.
 */
#define USE_LOW_POWER_IDLE  1

/* ============ DO HIEU NANG ============ */
#define PERF_ENABLE         1

#endif /* APP_CFG_H */
