/**
 * @file  hal_adc.h
 * @brief HAL ADC1 - doc hai truc joystick.
 * @owner DEV 2 - nhanh feature/hal-adc
 * @note  CHI task_hmi duoc goi hal_adc_read(). Dung o nhieu task thi phai
 *        them mutex, vi ADC1 chi co mot thanh ghi ket qua.
 */
#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <stdint.h>

#define ADC_MAX_COUNT   4095U
#define ADC_VREF_MV     3300U

/** @brief Bat clock ADC1, hieu chuan (calibration), cho phep chuyen doi. */
void hal_adc_init(void);

/**
 * @brief  Doc mot lan chuyen doi tren kenh chi dinh.
 * @param  channel  0..17
 * @return Gia tri raw 0..4095
 */
uint16_t hal_adc_read(uint8_t channel);

/** @brief Doi raw sang milivolt. */
static inline uint32_t hal_adc_to_mv(uint16_t raw)
{
    return ((uint32_t) raw * ADC_VREF_MV) / ADC_MAX_COUNT;
}

#endif /* HAL_ADC_H */
