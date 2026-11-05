/**
 * @file  hal_dma.h
 * @brief HAL DMA1 - cau hinh kenh va xu ly ngat bao xong.
 * @owner DEV 1 - nhanh feature/hal-dma
 *
 * Phan bo kenh (xem bsp.h):
 *   Kenh 1 : ADC1     - Dev 3
 *   Kenh 3 : SPI1_TX  - Dev 1, duong day khung hinh ra TFT
 */
#ifndef HAL_DMA_H
#define HAL_DMA_H

#include <stdint.h>
#include <stdbool.h>

/** @brief Bat clock DMA1 va dat uu tien NVIC cho kenh 3. */
void hal_dma_init(void);

/**
 * @brief Cau hinh kenh 3 cho mot lan truyen bo nho -> SPI1->DR.
 * @param src  Bo dem nguon, phai giu nguyen den khi truyen xong
 * @param len  So byte
 */
void hal_dma_spi_start(const uint8_t *src, uint16_t len);

/** @brief true neu kenh 3 dang truyen. */
bool hal_dma_spi_busy(void);

#endif /* HAL_DMA_H */
