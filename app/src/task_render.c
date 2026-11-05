/**
 * @file  task_render.c
 * @brief MODULE 1 - TODO: DEV 1 hien thuc. Xem app/inc/task_render.h
 */
#include "task_render.h"
#include "app_cfg.h"
#include "app_ipc.h"
#include "st7735.h"
#include "ssd1306.h"
#include "hal_spi.h"
#include "hal_dma.h"
#include "hal_uart.h"

static TaskHandle_t s_hTask = NULL;

/* KHUNG VONG LAP (Dev 1 dien vao):
 *
 * static void prvRenderTask(void *pv)
 * {
 *     for (;;) {
 *         // 1. Cho TASK_GAME bao "the gioi da cap nhat"
 *         xSemaphoreTake(g_xFrameSem, portMAX_DELAY);
 *
 *         uint32_t t0 = xTaskGetTickCount();
 *
 *         // 2. Chup mot ban world_t roi NHA MUTEX NGAY.
 *         //    Khong giu mutex suot 20 dai - TASK_GAME se bi chan.
 *         world_t snap;
 *         world_t *w = app_world_lock(5);
 *         if (w != NULL) { snap = *w; app_world_unlock(); }
 *
 *         // 3. Ve 20 dai
 *         for (uint8_t b = 0; b < TFT_BAND_COUNT; b++) {
 *             st7735_band_clear(COLOR_BLACK);
 *             // ve player, enemies, bullets, eggs trong dai b
 *             st7735_band_flush(b);
 *         }
 *         st7735_wait_idle();
 *
 *         // 4. Moi 500ms cap nhat OLED (dung ve moi khung, ton 24ms I2C)
 *         // 5. Ghi perf_stat_t qua app_perf_set()
 *     }
 * }
 *
 * BAY 1: chup world_t roi nha mutex ngay. Giu mutex ca khung = TASK_GAME
 *        bi chan 30ms moi lan -> tre dau vao, game giat.
 * BAY 2: OLED dung cap nhat moi khung. I2C 400kHz mat 24ms cho ca man hinh,
 *        an het ngan sach frame. Moi 500ms la du.
 */

bool task_render_hw_init(void)
{
    return false;   /* TODO */
}

BaseType_t task_render_create(void)
{
    (void) s_hTask;
    return pdFAIL;   /* TODO */
}
