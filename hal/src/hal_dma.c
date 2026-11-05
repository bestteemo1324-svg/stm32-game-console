/**
 * @file  hal_dma.c
 * @brief TODO: DEV 1 hien thuc theo dac ta trong hal/inc/hal_dma.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_dma.h"
#include "bsp.h"

/* TODO Dev 1:
 *   1. hal_dma_init(): bat clock DMA1, NVIC_SetPriority(DMA1_Channel3_IRQn,
 *      IRQ_PRIO_DMA_SPI), NVIC_EnableIRQ
 *   2. hal_dma_spi_start(): CPAR = &SPI1->DR, CMAR = src, CNDTR = len,
 *      CCR = MINC | DIR(doc tu bo nho) | TCIE, roi bat EN
 *   3. DMA1_Channel3_IRQHandler(): xoa co TC, tat kenh,
 *      xSemaphoreGiveFromISR(g_xDmaSem, &woken), portYIELD_FROM_ISR(woken)
 *
 * BAY: phai TAT kenh (CCR &= ~EN) truoc khi ghi CNDTR, khong thi khong an.
 *
 * TEST: dem so lan ISR chay trong 1 giay, so voi so dai da gui.
 */

/* ===== Than rong. Dev 1 dien vao. ===== */
void hal_dma_init(void) { }

void hal_dma_spi_start(const uint8_t *src, uint16_t len) { (void) src; (void) len; }

bool hal_dma_spi_busy(void) { return false; }
