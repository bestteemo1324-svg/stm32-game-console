/**
 * @file  app_ipc.h
 * @brief Doi tuong IPC dung chung - Queue, Semaphore, Mutex, Event group.
 * @owner LEADER. Task KHONG duoc tu tao kenh rieng de noi chuyen lien module.
 *
 *   [TASK_HMI] --g_xInputQueue--> [TASK_GAME] --g_xFrameSem--> [TASK_RENDER]
 *    prio 3                        prio 2      + g_xWorldMutex   prio 1
 *       ^                             ^                              ^
 *       |                             |                              |
 *   ISR nut bam              software timer                   ISR DMA xong
 *   (g_xBtnSem)              (sinh dot ga)                    (g_xDmaSem)
 */
#ifndef APP_IPC_H
#define APP_IPC_H

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"
#include "app_types.h"

/* ==================== HANG DOI ==================== */

/** @brief TASK_HMI -> TASK_GAME. Phan tu: input_evt_t */
extern QueueHandle_t g_xInputQueue;

/* ==================== SEMAPHORE ==================== */

/** @brief TASK_GAME -> TASK_RENDER: "the gioi da cap nhat, ve di". */
extern SemaphoreHandle_t g_xFrameSem;

/** @brief ISR DMA -> TASK_RENDER: "day xong mot dai, gui tiep duoc roi". */
extern SemaphoreHandle_t g_xDmaSem;

/** @brief ISR nut bam -> TASK_HMI. */
extern SemaphoreHandle_t g_xBtnSem;

/* ==================== MUTEX ==================== */

/** @brief Bao ve world_t khi TASK_GAME ghi va TASK_RENDER doc. */
extern SemaphoreHandle_t g_xWorldMutex;

/** @brief Bao ve UART khi nhieu task cung ghi log. */
extern SemaphoreHandle_t g_xUartMutex;

/* ==================== EVENT GROUP ==================== */
#define EVT_BIT_TFT_OK      (1U << 0)
#define EVT_BIT_OLED_OK     (1U << 1)
#define EVT_BIT_PLAYING     (1U << 2)

extern EventGroupHandle_t g_xSysEvents;

/* ==================== THE GIOI GAME ====================
 * TASK_GAME so huu. TASK_RENDER chi doc, luon qua hai ham duoi.
 */

/** @brief Lay quyen truy cap world_t. Tra NULL neu timeout. */
world_t *app_world_lock(uint32_t timeout_ms);

/** @brief Tra lai quyen truy cap. BAT BUOC goi sau moi lan lock thanh cong. */
void app_world_unlock(void);

/* ==================== SO LIEU HIEU NANG ==================== */
void app_perf_set(const perf_stat_t *p);
bool app_perf_get(perf_stat_t *out);

/* ==================== API ==================== */

/**
 * @brief  Tao toan bo doi tuong IPC.
 * @return true neu thanh cong. PHAI goi truoc khi tao task.
 */
bool app_ipc_init(void);

/** @brief Gui su kien tu TASK (khong phai ISR). Timeout 10ms. */
bool app_ipc_post_input(input_evt_id_t id, int8_t dx, int8_t dy);

#endif /* APP_IPC_H */
