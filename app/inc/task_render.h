/**
 * @file  task_render.h
 * @brief MODULE 1 - Hien thi. DEV 1 so huu.
 * @owner DEV 1 - nhanh feature/task-render
 *
 * TRACH NHIEM
 *   - Ve the gioi game vao dem dai, day ra TFT bang DMA (20 dai moi khung).
 *   - Cap nhat man OLED phu: FPS, tai CPU, heap con lai.
 *   - Do thoi gian ve va thoi gian truyen, ghi vao perf_stat_t.
 *
 * KHONG LAM
 *   - Khong sua world_t (chi doc qua app_world_lock).
 *   - Khong doc joystick, khong quyet dinh trang thai game.
 */
#ifndef TASK_RENDER_H
#define TASK_RENDER_H

#include "FreeRTOS.h"
#include "task.h"
#include <stdbool.h>

/** @brief Khoi tao SPI, DMA, TFT, OLED. Goi trong main() truoc khi tao task. */
bool task_render_hw_init(void);

/** @brief Tao task. Tra pdPASS neu thanh cong. */
BaseType_t task_render_create(void);

#endif /* TASK_RENDER_H */
