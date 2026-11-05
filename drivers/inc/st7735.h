/**
 * @file  st7735.h
 * @brief Driver TFT ST7735 128x160 - ve theo dai, day bang DMA.
 * @owner DEV 1 - nhanh feature/task-render
 *
 * TAI SAO VE THEO DAI:
 *   Mot khung day du = 128 x 160 x 2 byte = 40.960 byte.
 *   Blue Pill chi co 20.480 byte RAM. Khong nhet vua.
 *   Nen chia lam 20 dai, moi dai 128 x 8 pixel = 2.048 byte.
 *   Dung HAI dem: DMA day dem A trong khi CPU ve dem B, roi doi vai.
 *
 *   VONG LAP MOT KHUNG:
 *     for (dai = 0; dai < 20; dai++) {
 *         ve_cac_thuc_the_vao(dem_dang_ve, dai);
 *         cho_DMA_xong();            // semaphore g_xDmaSem
 *         doi_vai_hai_dem();
 *         bat_dau_DMA(dem_vua_ve);
 *     }
 */
#ifndef ST7735_H
#define ST7735_H

#include <stdint.h>
#include <stdbool.h>
#include "app_cfg.h"

/* Mau RGB565 */
#define RGB565(r, g, b)  ((uint16_t) (((r) & 0xF8) << 8 | ((g) & 0xFC) << 3 | (b) >> 3))
#define COLOR_BLACK      0x0000U
#define COLOR_WHITE      0xFFFFU
#define COLOR_RED        0xF800U
#define COLOR_GREEN      0x07E0U
#define COLOR_BLUE       0x001FU
#define COLOR_YELLOW     0xFFE0U

/**
 * @brief  Khoi tao man hinh: reset cung, chuoi lenh khoi tao, bat den nen.
 * @return true neu thanh cong.
 */
bool st7735_init(void);

/** @brief Dat cua so ghi. Goi truoc moi lan day mot dai. */
void st7735_set_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);

/**
 * @brief  Lay con tro toi dem dang ve (dem CPU duoc phep ghi).
 * @return Con tro toi TFT_BAND_PIXELS phan tu uint16_t.
 */
uint16_t *st7735_band_buffer(void);

/** @brief Xoa dem dang ve ve mot mau. */
void st7735_band_clear(uint16_t color);

/**
 * @brief Ve mot hinh chu nhat dac vao dem dang ve.
 * @param band_y  So thu tu dai dang ve (0..TFT_BAND_COUNT-1)
 * @note  Ham tu cat phan nam ngoai dai, caller khong can kiem tra.
 */
void st7735_band_fill_rect(uint8_t band_y, int16_t x, int16_t y,
                           uint8_t w, uint8_t h, uint16_t color);

/**
 * @brief Ve mot sprite 1-bit vao dem dang ve.
 * @param bitmap  Mang bit, moi bit mot pixel, MSB truoc
 */
void st7735_band_blit(uint8_t band_y, int16_t x, int16_t y,
                      uint8_t w, uint8_t h, const uint8_t *bitmap, uint16_t color);

/**
 * @brief  Day dem dang ve ra man hinh bang DMA, roi doi vai hai dem.
 * @note   Tra ve NGAY, khong cho DMA xong. Lan goi sau se tu cho.
 */
void st7735_band_flush(uint8_t band_y);

/** @brief Cho den khi DMA day xong dai cuoi cung. Goi o cuoi moi khung. */
void st7735_wait_idle(void);

#endif /* ST7735_H */
