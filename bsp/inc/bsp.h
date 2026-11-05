/**
 * @file  bsp.h
 * @brief So do chan va xung nhip - STM32F103C8T6 Blue Pill.
 * @owner LEADER. Cac Dev KHONG tu y doi chan. Can doi thi bao ca nhom.
 */
#ifndef BSP_H
#define BSP_H

#include "stm32f1xx.h"
#include <stdint.h>
#include <stdbool.h>

#define BSP_SYSCLK_HZ      72000000UL
#define BSP_APB1_HZ        36000000UL
#define BSP_APB2_HZ        72000000UL

/* ============ DEV 1: TFT ST7735 qua SPI1 ============
 * Module 8 chan: VCC GND SCK SDA CS DC RST BL
 * MISO (PA6) khong dung - TFT chi nhan, khong gui lai.
 */
#define PIN_TFT_SCK_PORT   GPIOA
#define PIN_TFT_SCK_PIN    5U      /* PA5 - SPI1_SCK      */
#define PIN_TFT_MOSI_PORT  GPIOA
#define PIN_TFT_MOSI_PIN   7U      /* PA7 - SPI1_MOSI     */
#define PIN_TFT_CS_PORT    GPIOA
#define PIN_TFT_CS_PIN     4U      /* PA4 - chip select   */
#define PIN_TFT_DC_PORT    GPIOA
#define PIN_TFT_DC_PIN     3U      /* PA3 - data/command  */
#define PIN_TFT_RST_PORT   GPIOA
#define PIN_TFT_RST_PIN    2U      /* PA2 - reset         */

/* ============ DEV 1: OLED SSD1306 qua I2C1 ============ */
#define PIN_I2C_SCL_PORT   GPIOB
#define PIN_I2C_SCL_PIN    6U      /* PB6 */
#define PIN_I2C_SDA_PORT   GPIOB
#define PIN_I2C_SDA_PIN    7U      /* PB7 */

/* ============ DEV 3: Joystick + nut bam ============ */
#define PIN_JOY_X_PORT     GPIOA
#define PIN_JOY_X_PIN      0U      /* PA0 - ADC1_IN0 */
#define ADC_CH_JOY_X       0U

#define PIN_JOY_Y_PORT     GPIOA
#define PIN_JOY_Y_PIN      1U      /* PA1 - ADC1_IN1 */
#define ADC_CH_JOY_Y       1U

#define PIN_BTN_FIRE_PORT  GPIOB
#define PIN_BTN_FIRE_PIN   12U     /* PB12 - nut BAN, EXTI12        */
#define PIN_BTN_MENU_PORT  GPIOB
#define PIN_BTN_MENU_PIN   13U     /* PB13 - START/PAUSE, EXTI13    */

/* Buzzer passive - TIM3_CH3. Khong dung PA6/PA7 vi trung SPI1. */
#define PIN_BUZZER_PORT    GPIOB
#define PIN_BUZZER_PIN     0U      /* PB0 - TIM3_CH3 PWM */

/* ============ DEV 3: UART debug ============ */
#define PIN_UART_TX_PORT   GPIOA
#define PIN_UART_TX_PIN    9U      /* PA9  */
#define PIN_UART_RX_PORT   GPIOA
#define PIN_UART_RX_PIN    10U     /* PA10 */

/* ============ Chung ============ */
#define PIN_LED_PORT       GPIOC
#define PIN_LED_PIN        13U     /* PC13 - tich cuc muc THAP */

/* ============ Phan bo kenh DMA1 ============
 *   Kenh 1 : ADC1     (Dev 3)
 *   Kenh 3 : SPI1_TX  (Dev 1)  <- duong day khung hinh ra TFT
 *   Cac kenh khac con trong.
 */

/** @brief HSE 8MHz -> PLL x9 -> 72MHz, bat clock GPIO va AFIO. */
void bsp_system_init(void);

/** @brief Delay vong lap. CHI dung truoc khi scheduler chay. */
void bsp_delay_ms_blocking(uint32_t ms);

#endif /* BSP_H */
