/**
 * @file  hal_gpio.c
 * @brief TODO: DEV 3 hien thuc theo dac ta trong hal/inc/hal_gpio.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_gpio.h"
#include "bsp.h"

/* TODO Dev 3:
 *   1. prv_mode_bits(): doi gpio_mode_t sang 4 bit CNF:MODE cua F1
 *   2. hal_gpio_config(): ghi vao CRL (chan 0-7) hoac CRH (chan 8-15)
 *      Luu y: input pull-up/pull-down dung chung CNF=10, huong keo do bit ODR
 *   3. hal_gpio_write(): dung BSRR, KHONG dung ODR (ODR khong atomic)
 *   4. hal_gpio_exti_falling(): AFIO->EXTICR, EXTI->IMR/FTSR, NVIC_SetPriority
 *   5. hal_gpio_init_all(): cau hinh het chan trong bsp.h, dat trang thai an toan
 *
 * TEST: nhay LED PC13, bam nut thay ISR chay (dat breakpoint hoac bat LED).
 */

/* ===== Than rong de repo build duoc tu ngay dau. Dev 3 dien vao. ===== */
void hal_gpio_config(GPIO_TypeDef *port, uint8_t pin, gpio_mode_t mode)
{
    (void) port; (void) pin; (void) mode;
}

void hal_gpio_write(GPIO_TypeDef *port, uint8_t pin, bool level)
{
    (void) port; (void) pin; (void) level;
}

void hal_gpio_toggle(GPIO_TypeDef *port, uint8_t pin)
{
    (void) port; (void) pin;
}

bool hal_gpio_read(GPIO_TypeDef *port, uint8_t pin)
{
    (void) port; (void) pin;
    return false;
}

void hal_gpio_exti_falling(GPIO_TypeDef *port, uint8_t pin, uint32_t nvic_prio)
{
    (void) port; (void) pin; (void) nvic_prio;
}

void hal_gpio_init_all(void)
{
}
