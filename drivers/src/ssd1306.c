/**
 * @file  ssd1306.c
 * @brief TODO: DEV 1 hien thuc theo dac ta trong drivers/inc/ssd1306.h
 *
 * Driver nay co the chep lai tu do an he thong chua chay ky truoc,
 * chi can doi ten ham cho khop header. Day la phan nhe nhat cua Dev 1.
 */
#include "ssd1306.h"
#include "hal_i2c.h"

static uint8_t s_fb[8][128];   /* framebuffer 1 KB, nam gon trong RAM */

/* TODO Dev 1:
 *   1. Bang font 5x7 cho ASCII 0x20..0x5F
 *   2. ssd1306_init(): kiem tra ACK tai 0x3C, gui chuoi lenh khoi tao
 *   3. ssd1306_draw_string(): ghi bit vao s_fb
 *   4. ssd1306_update(): voi moi page, gui lenh chon page roi 128 byte du lieu
 */

/* ===== Than rong. Dev 1 dien vao. ===== */
bool ssd1306_init(void) { return false; }

void ssd1306_clear(void) { (void) s_fb; }

void ssd1306_draw_string(uint8_t x, uint8_t page, const char *str, bool invert)
{
    (void) x; (void) page; (void) str; (void) invert;
}

void ssd1306_draw_bar(uint8_t x, uint8_t page, uint8_t width, uint8_t percent)
{
    (void) x; (void) page; (void) width; (void) percent;
}

bool ssd1306_update(void) { return false; }
