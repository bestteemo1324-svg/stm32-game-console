/**
 * @file  app_ipc.c
 * @brief Hien thuc cac doi tuong IPC dung chung.
 * @owner LEADER
 */
#include "app_ipc.h"
#include "app_cfg.h"
#include <string.h>

QueueHandle_t      g_xInputQueue = NULL;
SemaphoreHandle_t  g_xFrameSem   = NULL;
SemaphoreHandle_t  g_xDmaSem     = NULL;
SemaphoreHandle_t  g_xBtnSem     = NULL;
SemaphoreHandle_t  g_xWorldMutex = NULL;
SemaphoreHandle_t  g_xUartMutex  = NULL;
EventGroupHandle_t g_xSysEvents  = NULL;

static world_t     s_world;
static perf_stat_t s_perf;

bool app_ipc_init(void)
{
    g_xInputQueue = xQueueCreate(Q_INPUT_LEN, sizeof(input_evt_t));
    g_xFrameSem   = xSemaphoreCreateBinary();
    g_xDmaSem     = xSemaphoreCreateBinary();
    g_xBtnSem     = xSemaphoreCreateBinary();
    g_xWorldMutex = xSemaphoreCreateMutex();
    g_xUartMutex  = xSemaphoreCreateMutex();
    g_xSysEvents  = xEventGroupCreate();

    if ((g_xInputQueue == NULL) || (g_xFrameSem == NULL) || (g_xDmaSem == NULL) ||
        (g_xBtnSem == NULL) || (g_xWorldMutex == NULL) || (g_xUartMutex == NULL) ||
        (g_xSysEvents == NULL)) {
        return false;
    }

    vQueueAddToRegistry(g_xInputQueue, "INPUT_Q");

    (void) memset(&s_world, 0, sizeof(s_world));
    (void) memset(&s_perf, 0, sizeof(s_perf));
    s_world.state = GS_BOOT;

    return true;
}

world_t *app_world_lock(uint32_t timeout_ms)
{
    if (xSemaphoreTake(g_xWorldMutex, pdMS_TO_TICKS(timeout_ms)) == pdTRUE) {
        return &s_world;
    }
    return NULL;   /* Caller PHAI kiem tra NULL - khong duoc dung bua */
}

void app_world_unlock(void)
{
    (void) xSemaphoreGive(g_xWorldMutex);
}

bool app_ipc_post_input(input_evt_id_t id, int8_t dx, int8_t dy)
{
    input_evt_t evt = {
        .id   = id,
        .dx   = dx,
        .dy   = dy,
        .tick = (uint32_t) xTaskGetTickCount()
    };
    /* Timeout 10ms - khong bao gio block vinh vien */
    return (xQueueSend(g_xInputQueue, &evt, pdMS_TO_TICKS(10)) == pdPASS);
}

void app_perf_set(const perf_stat_t *p)
{
    if (p != NULL) {
        s_perf = *p;
    }
}

bool app_perf_get(perf_stat_t *out)
{
    if (out == NULL) {
        return false;
    }
    *out = s_perf;
    return true;
}

const char *app_state_name(game_state_t st)
{
    static const char *const names[GS_COUNT] = {
        "BOOT", "MENU", "PLAYING", "PAUSED", "GAMEOVER"
    };
    return (st < GS_COUNT) ? names[st] : "???";
}
