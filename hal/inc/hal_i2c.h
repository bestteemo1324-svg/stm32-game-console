/**
 * @file  hal_i2c.h
 * @brief HAL I2C1 master - phuc vu OLED SSD1306.
 * @owner DEV 2 - nhanh feature/hal-i2c
 * @note  Moi ham co TIMEOUT, khong bao gio treo task. Tra false neu that bai.
 */
#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>
#include <stdbool.h>

/** @brief Khoi tao I2C1 Fast Mode 400 kHz. */
void hal_i2c_init(void);

/**
 * @brief  Ghi mot khoi toi slave.
 * @param  addr7  Dia chi 7 bit (OLED = 0x3C)
 * @return true neu thanh cong, false neu timeout hoac NACK
 */
bool hal_i2c_write(uint8_t addr7, const uint8_t *data, uint16_t len);

/** @brief Kiem tra slave co tra ACK khong. Dung de do thiet bi. */
bool hal_i2c_is_ready(uint8_t addr7);

#endif /* HAL_I2C_H */
