/**
 * @file  task_hmi.h
 * @brief MODULE 3 - Giao dien nguoi dung. DEV 3 so huu.
 * @owner DEV 3 - nhanh feature/task-hmi
 *
 * TRACH NHIEM
 *   - Doc joystick qua ADC, loc vung chet, gui su kien vao g_xInputQueue.
 *   - Nhan nut BAN va START/PAUSE qua ngat ngoai EXTI.
 *   - Phat am thanh hieu ung bang PWM.
 *   - Ghi nhat ky va so lieu do ra UART.
 *   - Nuoi watchdog.
 *
 * KHONG LAM
 *   - Khong sua world_t. Chi gui su kien, TASK_GAME quyet dinh.
 *   - Khong ve man hinh.
 */
#ifndef TASK_HMI_H
#define TASK_HMI_H

#include "FreeRTOS.h"
#include "task.h"

/** @brief Am thanh hieu ung trong game. */
typedef enum {
    SFX_NONE = 0,
    SFX_SHOOT,
    SFX_HIT,
    SFX_LOSE_LIFE,
    SFX_WAVE_CLEAR
} sfx_id_t;

/** @brief Khoi tao ADC, GPIO nut bam, EXTI, PWM. Goi trong main(). */
void task_hmi_hw_init(void);

/** @brief Yeu cau phat mot hieu ung. Goi duoc tu task khac. */
void task_hmi_play_sfx(sfx_id_t id);

/** @brief Tao task. */
BaseType_t task_hmi_create(void);

#endif /* TASK_HMI_H */
