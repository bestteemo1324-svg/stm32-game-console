/**
 * @file  task_game.c
 * @brief MODULE 2 - TODO: DEV 2 hien thuc. Xem app/inc/task_game.h
 *
 * QUY TAC: file nay KHONG goi ham HAL nao, khong dong toi thanh ghi nao.
 * Nho vay ba ham thuan o cuoi file bien dich duoc tren PC de chay unit test.
 */
#include "task_game.h"
#include "app_cfg.h"
#include "app_ipc.h"

static TaskHandle_t s_hTask = NULL;

/* KHUNG VONG LAP (Dev 2 dien vao):
 *
 * static void prvGameTask(void *pv)
 * {
 *     TickType_t last = xTaskGetTickCount();
 *     for (;;) {
 *         // 1. Vet het su kien dau vao dang cho (khong block)
 *         input_evt_t ev;
 *         while (xQueueReceive(g_xInputQueue, &ev, 0) == pdPASS) {
 *             prv_handle_input(&ev);
 *         }
 *
 *         // 2. Cap nhat the gioi theo trang thai hien tai
 *         world_t *w = app_world_lock(10);
 *         if (w != NULL) {
 *             switch (w->state) {
 *                 case GS_PLAYING: prv_update_playing(w); break;
 *                 ...
 *             }
 *             app_world_unlock();
 *         }
 *
 *         // 3. Bao TASK_RENDER ve lai
 *         xSemaphoreGive(g_xFrameSem);
 *
 *         vTaskDelayUntil(&last, pdMS_TO_TICKS(GAME_TICK_MS));
 *     }
 * }
 *
 * THU TU LAM:
 *   B1. Ba ham thuan duoi + unit test tren PC. CHUA CAN KIT.
 *   B2. Nguoi choi di chuyen duoc theo joystick.
 *   B3. Ban dan, dan bay len, bien mat khi ra khoi man.
 *   B4. Ga xuat hien, va cham, tinh diem.
 *   B5. May trang thai day du + 3 dot ga.
 */

/* ================= HAM THUAN - CO UNIT TEST =================
 * Ba ham duoi khong dung FreeRTOS, khong dung bien toan cuc.
 * tests/test_game.c bien dich truc tiep file nay tren PC.
 */

bool game_aabb_overlap(const entity_t *a, const entity_t *b)
{
    (void) a; (void) b;
    return false;   /* TODO Dev 2 */
}

uint16_t game_score_for_kill(uint8_t wave)
{
    (void) wave;
    return 0U;   /* TODO Dev 2: dot sau diem cao hon */
}

void game_wave_params(uint8_t wave, uint8_t *out_count, int16_t *out_speed)
{
    (void) wave; (void) out_count; (void) out_speed;
    /* TODO Dev 2: dot 1 it ga cham, dot 3 nhieu ga nhanh */
}

BaseType_t task_game_create(void)
{
    (void) s_hTask;
    return pdFAIL;   /* TODO */
}
