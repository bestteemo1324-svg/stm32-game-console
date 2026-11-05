/**
 * @file  hal_adc.c
 * @brief TODO: DEV 2 hien thuc theo dac ta trong hal/inc/hal_adc.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_adc.h"
#include "bsp.h"

/* TODO Dev 2:
 *   1. hal_adc_init(): bat clock ADC1, SMPR2 dat thoi gian lay mau 55.5 chu ky
 *      cho kenh 0 va 1, bat ADON, cho on dinh, RSTCAL roi CAL
 *   2. hal_adc_read(): SQR3 = channel, ghi ADON lan hai de khoi dong,
 *      cho co EOC, doc DR
 *
 * BAY: ADC clock toi da 14 MHz. APB2/6 = 12 MHz la dung, dung dat /2 hay /4.
 *
 * TEST: xoay joystick, in gia tri raw ra UART, phai chay muot 0..4095.
 */

/* ===== Than rong. Dev 2 dien vao. ===== */
void hal_adc_init(void) { }

uint16_t hal_adc_read(uint8_t channel) { (void) channel; return 0U; }
