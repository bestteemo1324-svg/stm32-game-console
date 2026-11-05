/**
 * @file  ssd1306.h
 * @brief Driver OLED SSD1306 128x64 - man phu hien so lieu.
 * @owner DEV 1 - nhanh feature/task-render
 * @note  Framebuffer 1024 byte nam gon trong RAM, khong can chia dai nhu TFT.
 *        Co the chep lai tu do an he thong chua chay cua ky truoc.
 */
#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define SSD1306_I2C_ADDR   0x3CU

/** @brief Khoi tao man hinh. Tra false neu khong thay thiet bi tren bus. */
bool ssd1306_init(void);

/** @brief Xoa framebuffer (chua day ra man hinh). */
void ssd1306_clear(void);

/** @brief Ve chuoi font 5x7. Chu thuong tu dong doi thanh IN HOA. */
void ssd1306_draw_string(uint8_t x, uint8_t page, const char *str, bool invert);

/** @brief Ve thanh tien trinh ngang. */
void ssd1306_draw_bar(uint8_t x, uint8_t page, uint8_t width, uint8_t percent);

/** @brief Day framebuffer ra man hinh. */
bool ssd1306_update(void);

#endif /* SSD1306_H */
