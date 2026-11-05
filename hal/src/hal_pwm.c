/**
 * @file  hal_pwm.c
 * @brief TODO: DEV 3 hien thuc theo dac ta trong hal/inc/hal_pwm.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_pwm.h"
#include "bsp.h"

/* TODO Dev 3:
 *   1. hal_pwm_init(): bat clock TIM3 + GPIOB, PB0 che do AF_PP,
 *      CCMR2 dat kenh 3 che do PWM1, CCER bat CC3E, PSC chia ve 1 MHz
 *   2. hal_pwm_tone(): freq = 0 thi tat CEN va keo chan xuong thap.
 *      Khac 0 thi ARR = 1000000 / freq - 1, CCR3 = ARR / 2 (duty 50%),
 *      EGR = UG de nap ngay, bat CEN
 *
 * BAY: buzzer PASSIVE moi doi duoc tan so. Buzzer active chi keu mot tong.
 *
 * TEST: phat lan luot 262, 330, 392 Hz - nghe ra ba not Do Mi Sol.
 */

/* ===== Than rong. Dev 3 dien vao. ===== */
void hal_pwm_init(void) { }

void hal_pwm_tone(uint16_t freq_hz) { (void) freq_hz; }

void hal_pwm_mute(void) { }
