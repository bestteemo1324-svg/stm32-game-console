/**
 * @file  st7735.c
 * @brief TODO: DEV 1 hien thuc theo dac ta trong drivers/inc/st7735.h
 */
#include "st7735.h"
#include "hal_spi.h"
#include "hal_gpio.h"
#include "bsp.h"
#include "app_ipc.h"

/* HAI dem dai: DMA day dem nay trong khi CPU ve dem kia.
 * 2 x 2048 = 4096 byte - chiem 20% RAM cua board, dung tang TFT_BAND_H.
 */
static uint16_t s_band[2][TFT_BAND_PIXELS];
static uint8_t  s_draw_idx;   /* dem CPU dang ve (0 hoac 1) */

/* TODO Dev 1:
 *   1. st7735_init(): keo RST xuong 50ms roi len, gui chuoi lenh khoi tao
 *      (SWRESET 0x01, SLPOUT 0x11, COLMOD 0x3A = 0x05 cho RGB565,
 *       MADCTL 0x36, DISPON 0x29). Giua cac lenh co cho tre theo datasheet.
 *   2. st7735_set_window(): gui CASET 0x2A, RASET 0x2B, roi RAMWR 0x2C
 *   3. st7735_band_fill_rect(): cat phan nam ngoai dai hien tai, ghi mau
 *      vao s_band[s_draw_idx]
 *   4. st7735_band_flush(): cho g_xDmaSem (DMA cu da xong chua),
 *      doi s_draw_idx, set_window cho dai nay, hal_spi_write_dma()
 *
 * TAI SAO DOI DEM: neu chi co mot dem, CPU phai dung cho DMA day xong
 * moi ve tiep duoc -> mat het loi ich cua DMA.
 *
 * THU TU LAM (dung lam het mot luc):
 *   B1. Khoi tao + to ca man hinh mot mau. Thay mau = SPI va lenh dung.
 *   B2. Ve mot hinh chu nhat dung vi tri. Thay = toa do va cua so dung.
 *   B3. Ve theo 20 dai bang SPI blocking. Thay hinh day du = logic dai dung.
 *   B4. Doi sang DMA hai dem. Do FPS truoc va sau -> so lieu cho bao cao.
 */

/* ===== Than rong. Dev 1 dien vao. ===== */
bool st7735_init(void) { return false; }

void st7735_set_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
    (void) x0; (void) y0; (void) x1; (void) y1;
}

uint16_t *st7735_band_buffer(void) { return s_band[s_draw_idx]; }

void st7735_band_clear(uint16_t color) { (void) color; }

void st7735_band_fill_rect(uint8_t band_y, int16_t x, int16_t y,
                           uint8_t w, uint8_t h, uint16_t color)
{
    (void) band_y; (void) x; (void) y; (void) w; (void) h; (void) color;
}

void st7735_band_blit(uint8_t band_y, int16_t x, int16_t y,
                      uint8_t w, uint8_t h, const uint8_t *bitmap, uint16_t color)
{
    (void) band_y; (void) x; (void) y; (void) w; (void) h;
    (void) bitmap; (void) color;
}

void st7735_band_flush(uint8_t band_y) { (void) band_y; }

void st7735_wait_idle(void) { }
