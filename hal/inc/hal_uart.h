/**
 * @file  hal_uart.h
 * @brief HAL USART1 - ghi nhat ky va so lieu do ve may tinh.
 * @owner DEV 3 - nhanh feature/hal-uart
 * @note  hal_uart_puts() THREAD-SAFE: tu lay g_xUartMutex khi scheduler chay.
 */
#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

/** @brief Khoi tao USART1 115200-8N1. */
void hal_uart_init(uint32_t baudrate);

/** @brief Gui mot byte (blocking). */
void hal_uart_putc(char c);

/** @brief Gui chuoi. Thread-safe. */
void hal_uart_puts(const char *str);

/** @brief Log co tien to tick: "[  12345] noi dung". Thread-safe. */
void hal_uart_log(const char *str);

#endif /* HAL_UART_H */
