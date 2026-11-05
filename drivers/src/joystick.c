/**
 * @file  joystick.c
 * @brief TODO: DEV 3 hien thuc theo dac ta trong drivers/inc/joystick.h
 */
#include "joystick.h"
#include <stddef.h>
#include "hal_adc.h"
#include "bsp.h"
#include "app_cfg.h"

static uint16_t s_center_x = JOY_CENTER;
static uint16_t s_center_y = JOY_CENTER;

/* TODO Dev 3:
 *   1. joystick_calibrate(): doc 32 mau moi truc, lay trung binh, luu vao
 *      s_center_x / s_center_y. Nguoi choi KHONG duoc cham joystick luc nay.
 *   2. joystick_read(): doc raw, tru tam da hieu chuan, neu tri tuyet doi
 *      nho hon JOY_DEADZONE thi tra 0, con lai thi chuan hoa ve -100..100
 *
 * BAY: truc Y cua module thuong nguoc chieu voi truc Y man hinh.
 *      Thu roi dao dau neu nhan vat di nguoc.
 *
 * TEST: in dx, dy ra UART. Tha tay phai ra 0,0 on dinh, khong nhay.
 */

/* ===== Than rong. Dev 3 dien vao. ===== */
void joystick_init(void) { }

void joystick_calibrate(void) { (void) s_center_x; (void) s_center_y; }

void joystick_read(joy_state_t *out)
{
    if (out != NULL) {
        out->dx = 0;
        out->dy = 0;
        out->moved = false;
    }
}
