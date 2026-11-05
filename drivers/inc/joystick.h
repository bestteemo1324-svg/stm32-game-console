/**
 * @file  joystick.h
 * @brief Driver joystick analog hai truc - doc ADC va loc vung chet.
 * @owner DEV 3 - nhanh feature/task-hmi
 *
 * TAI SAO CAN VUNG CHET:
 *   Joystick tha tay khong bao gio ve dung 2048. Moi module lech mot kieu,
 *   thuong dao dong 1900..2200. Khong loc thi nhan vat tu troi.
 *   Cach lam: lech khoi tam duoi JOY_DEADZONE thi coi nhu khong di chuyen.
 */
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int8_t dx;        /**< -100..100, 0 neu nam trong vung chet */
    int8_t dy;
    bool   moved;     /**< true neu khac lan doc truoc          */
} joy_state_t;

/** @brief Khoi tao chan ADC cho hai truc. */
void joystick_init(void);

/**
 * @brief Do tam thuc te luc khoi dong (nguoi choi khong duoc cham joystick).
 * @note  Goi mot lan trong task_hmi truoc vong lap chinh. Lay trung binh
 *        32 mau de bu sai lech cua tung module.
 */
void joystick_calibrate(void);

/** @brief Doc va chuan hoa vi tri hien tai. */
void joystick_read(joy_state_t *out);

#endif /* JOYSTICK_H */
