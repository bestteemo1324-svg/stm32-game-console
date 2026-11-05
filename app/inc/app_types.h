/**
 * @file  app_types.h
 * @brief Kieu du lieu dung chung - HOP DONG GIAO TIEP giua 3 module.
 * @owner LEADER. Sua file nay = sua giao dien chung, phai bao ca nhom.
 */
#ifndef APP_TYPES_H
#define APP_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "app_cfg.h"

/* ==================== MAY TRANG THAI ====================
 *
 *   +------+   xong    +------+  nut START  +---------+
 *   | BOOT |---------->| MENU |------------>| PLAYING |<---+
 *   +------+           +------+             +----+----+    |
 *                          ^                     |         | nut START
 *                          |                het mang   +---+----+
 *                   nut START                    |      | PAUSED |
 *                          |                     v      +--------+
 *                     +-----------+ <------------+
 *                     | GAME_OVER |
 *                     +-----------+
 */
typedef enum {
    GS_BOOT = 0,
    GS_MENU,
    GS_PLAYING,
    GS_PAUSED,
    GS_GAME_OVER,
    GS_COUNT
} game_state_t;

/* ==================== SU KIEN DAU VAO ==================== */
typedef enum {
    IN_NONE = 0,
    IN_MOVE,        /**< Joystick doi vi tri, kem dx/dy */
    IN_FIRE_DOWN,
    IN_FIRE_UP,
    IN_MENU_PRESS   /**< Nut START/PAUSE                */
} input_evt_id_t;

/** @brief Goi su kien TASK_HMI -> TASK_GAME qua g_xInputQueue. */
typedef struct {
    input_evt_id_t id;
    int8_t         dx;    /**< -100..100, da chuan hoa tu ADC */
    int8_t         dy;
    uint32_t       tick;
} input_evt_t;

/* ==================== THUC THE ==================== */
typedef enum {
    ET_NONE = 0,
    ET_PLAYER,
    ET_CHICKEN,
    ET_BULLET,
    ET_EGG
} entity_type_t;

/**
 * @brief Mot thuc the trong game. Toa do Q12.4 (xem app_cfg.h).
 * @note  Giu struct NHO - toan bo world_t phai nam gon trong RAM 20 KB.
 */
typedef struct {
    int16_t x, y;     /**< Vi tri, Q12.4                */
    int16_t vx, vy;   /**< Van toc, Q12.4 moi tick      */
    uint8_t type;     /**< entity_type_t                */
    uint8_t w, h;     /**< Hop va cham, don vi pixel    */
    uint8_t hp;
    bool    alive;
} entity_t;

/**
 * @brief Toan bo trang thai the gioi.
 * @note  TASK_GAME ghi, TASK_RENDER doc. Truy cap qua g_xWorldMutex.
 */
typedef struct {
    game_state_t state;
    entity_t     player;
    entity_t     enemies[MAX_ENEMIES];
    entity_t     bullets[MAX_BULLETS];
    entity_t     eggs[MAX_EGGS];
    uint16_t     score;
    uint16_t     hi_score;
    uint8_t      lives;
    uint8_t      wave;
    uint8_t      enemies_alive;
} world_t;

/* ==================== SO LIEU HIEU NANG ====================
 * Phuc vu muc "Danh gia hoat dong" va "Phan tich lap lich" trong bao cao.
 */
typedef struct {
    uint16_t fps;
    uint16_t frame_ms;      /**< Trung binh mot khung           */
    uint16_t draw_ms;       /**< CPU ve vao dem dai             */
    uint16_t transfer_ms;   /**< DMA day ra TFT                 */
    uint8_t  cpu_load_pct;
    uint16_t heap_free;
} perf_stat_t;

/** @brief Doi trang thai sang chuoi de hien thi / ghi log. */
const char *app_state_name(game_state_t st);

#endif /* APP_TYPES_H */
