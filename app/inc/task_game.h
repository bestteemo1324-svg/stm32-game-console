/**
 * @file  task_game.h
 * @brief MODULE 2 - Game engine. DEV 2 so huu.
 * @owner DEV 2 - nhanh feature/task-game
 *
 * TRACH NHIEM
 *   - Giu world_t: nguoi choi, ga, dan, trung.
 *   - Cap nhat vi tri, phat hien va cham, tinh diem, sinh dot ga.
 *   - Giu may trang thai BOOT/MENU/PLAYING/PAUSED/GAME_OVER.
 *   - Bao TASK_RENDER ve lai bang g_xFrameSem sau moi lan cap nhat.
 *
 * KHONG LAM
 *   - Khong dong toi phan cung. Khong goi ham HAL nao.
 *   - Nho vay toan bo file nay bien dich duoc tren PC de chay unit test.
 */
#ifndef TASK_GAME_H
#define TASK_GAME_H

#include "FreeRTOS.h"
#include "task.h"
#include "app_types.h"

/** @brief Tao task. */
BaseType_t task_game_create(void);

/* ===== Ham thuan, khong phu thuoc phan cung - CO UNIT TEST =====
 * Ba ham duoi duoc test tren PC bang tests/test_game.c.
 * Giu chung KHONG goi FreeRTOS va KHONG dung bien toan cuc.
 */

/** @brief Hai hop chu nhat co cham nhau khong (toa do Q12.4). */
bool game_aabb_overlap(const entity_t *a, const entity_t *b);

/** @brief Diem cong khi ban trung mot ga o dot thu wave. */
uint16_t game_score_for_kill(uint8_t wave);

/** @brief So ga va toc do roi cua dot thu wave. */
void game_wave_params(uint8_t wave, uint8_t *out_count, int16_t *out_speed);

#endif /* TASK_GAME_H */
