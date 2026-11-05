/**
 * @file  hal_spi.h
 * @brief HAL SPI1 master - duong day du lieu ra TFT.
 * @owner DEV 1 - nhanh feature/hal-spi
 *
 * TFT chi nhan du lieu nen cau hinh che do chi gui (transmit only),
 * khong doc MISO. Toc do dat APB2/4 = 18 MHz.
 */
#ifndef HAL_SPI_H
#define HAL_SPI_H

#include <stdint.h>
#include <stdbool.h>

/** @brief Khoi tao SPI1: master, mode 0, MSB first, 18 MHz, 8 bit. */
void hal_spi_init(void);

/** @brief Gui mot byte, cho xong. Dung cho lenh dieu khien TFT. */
void hal_spi_write_byte(uint8_t b);

/** @brief Gui mot khoi, cho xong (blocking). Dung luc khoi tao. */
void hal_spi_write(const uint8_t *data, uint16_t len);

/**
 * @brief  Gui mot khoi bang DMA, KHONG cho xong - tra ve ngay.
 * @note   Khi xong, ISR DMA se giai phong g_xDmaSem.
 *         Caller phai cho semaphore do truoc khi sua lai bo dem.
 * @return false neu DMA dang ban.
 */
bool hal_spi_write_dma(const uint8_t *data, uint16_t len);

/** @brief true neu DMA con dang truyen. */
bool hal_spi_dma_busy(void);

#endif /* HAL_SPI_H */
