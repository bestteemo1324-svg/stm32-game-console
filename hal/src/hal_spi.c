/**
 * @file  hal_spi.c
 * @brief TODO: DEV 1 hien thuc theo dac ta trong hal/inc/hal_spi.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_spi.h"
#include <stddef.h>
#include "bsp.h"

/* TODO Dev 1:
 *   1. hal_spi_init(): bat clock SPI1 + GPIO, cau hinh PA5/PA7 che do AF_PP,
 *      CR1 = master, mode 0 (CPOL=0 CPHA=0), BR = APB2/4, MSB first, SSM+SSI
 *   2. hal_spi_write_byte(): cho TXE, ghi DR, cho BSY ha
 *   3. hal_spi_write(): lap lai write_byte (blocking, chi dung luc init)
 *   4. hal_spi_write_dma(): bat SPI1->CR2 TXDMAEN roi goi hal_dma_spi_start()
 *
 * BAY: sau khi gui byte cuoi phai cho co BSY ha truoc khi keo CS len,
 *      khong thi byte cuoi bi cat.
 *
 * TEST: gui 0x00 lien tuc, soi oscilloscope hoac logic analyzer chan PA5/PA7.
 */

/* ===== Than rong. Dev 1 dien vao. ===== */
void hal_spi_init(void) { }

void hal_spi_write_byte(uint8_t b) { (void) b; }

void hal_spi_write(const uint8_t *data, uint16_t len) { (void) data; (void) len; }

bool hal_spi_write_dma(const uint8_t *data, uint16_t len)
{
    (void) data; (void) len;
    return false;
}

bool hal_spi_dma_busy(void) { return false; }
