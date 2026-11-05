/**
 * @file  hal_gpio.h
 * @brief HAL GPIO - truy cap thanh ghi truc tiep (bare-metal).
 * @owner DEV 3 - nhanh feature/hal-gpio
 */
#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include "stm32f1xx.h"
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    GPIO_MODE_INPUT_FLOAT = 0,
    GPIO_MODE_INPUT_PU,
    GPIO_MODE_INPUT_PD,
    GPIO_MODE_ANALOG,
    GPIO_MODE_OUTPUT_PP,
    GPIO_MODE_OUTPUT_OD,
    GPIO_MODE_AF_PP,
    GPIO_MODE_AF_OD
} gpio_mode_t;

/** @brief Cau hinh mot chan. */
void hal_gpio_config(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode);

/** @brief Ghi muc logic. Dung BSRR nen atomic, an toan voi RTOS. */
void hal_gpio_write(GPIO_TypeDef *port, uint8_t pin, bool level);

/** @brief Dao trang thai chan. */
void hal_gpio_toggle(GPIO_TypeDef *port, uint8_t pin);

/** @brief Doc muc logic. */
bool hal_gpio_read(GPIO_TypeDef *port, uint8_t pin);

/**
 * @brief Cau hinh ngat ngoai canh xuong.
 * @param nvic_prio PHAI >= configMAX_SYSCALL_INTERRUPT_PRIORITY neu ISR
 *                  co goi API ...FromISR().
 */
void hal_gpio_exti_falling(GPIO_TypeDef *port, uint8_t pin, uint32_t nvic_prio);

/** @brief Khoi tao toan bo chan so cua board. Goi mot lan trong main(). */
void hal_gpio_init_all(void);

#endif /* HAL_GPIO_H */
