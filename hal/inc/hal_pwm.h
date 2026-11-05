/**
 * @file  hal_pwm.h
 * @brief HAL TIM3_CH3 PWM - phat am thanh qua buzzer passive.
 * @owner DEV 3 - nhanh feature/hal-timer-pwm
 *
 * Buzzer passive khong co mach dao dong, phai cap song vuong.
 * Doi tan so bang cach doi ARR, giu duty 50% de am to nhat.
 */
#ifndef HAL_PWM_H
#define HAL_PWM_H

#include <stdint.h>

/** @brief Khoi tao TIM3_CH3 che do PWM, ban dau tat tieng. */
void hal_pwm_init(void);

/**
 * @brief Phat mot tan so.
 * @param freq_hz  Tan so (Hz). Truyen 0 de TAT tieng.
 *                 Dai nghe duoc hop ly: 200..4000 Hz.
 */
void hal_pwm_tone(uint16_t freq_hz);

/** @brief Tat tieng ngay. Tuong duong hal_pwm_tone(0). */
void hal_pwm_mute(void);

#endif /* HAL_PWM_H */
