/**
 * @file  hal_i2c.c
 * @brief TODO: DEV 2 hien thuc theo dac ta trong hal/inc/hal_i2c.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_i2c.h"
#include <stddef.h>
#include "bsp.h"

/* TODO Dev 2:
 *   1. hal_i2c_init(): bat clock, PB6/PB7 che do AF_OD, SWRST roi bo,
 *      CR2 = 36 (MHz APB1), CCR = FS | 30, TRISE = 11, bat PE
 *   2. hal_i2c_write(): START -> cho SB -> gui dia chi -> cho ADDR (hoac AF
 *      neu NACK) -> doc SR1,SR2 de xoa ADDR -> gui tung byte cho TXE ->
 *      cho BTF -> STOP
 *
 * BAT BUOC: moi vong cho co phai co bo dem timeout, het han thi STOP va
 *           tra false. Treo o day la treo ca he thong.
 *
 * TEST: hal_i2c_is_ready(0x3C) tra true khi cam OLED, false khi rut day.
 */

/* ===== Than rong. Dev 2 dien vao. ===== */
void hal_i2c_init(void) { }

bool hal_i2c_write(uint8_t addr7, const uint8_t *data, uint16_t len)
{
    (void) addr7; (void) data; (void) len;
    return false;
}

bool hal_i2c_is_ready(uint8_t addr7) { (void) addr7; return false; }
