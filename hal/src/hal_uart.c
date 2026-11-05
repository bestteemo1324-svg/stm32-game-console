/**
 * @file  hal_uart.c
 * @brief TODO: DEV 3 hien thuc theo dac ta trong hal/inc/hal_uart.h
 *
 * CHUA VIET. Doc header truoc, hien thuc tung ham, test tren kit roi hay commit.
 * Commit nhieu lan theo tien do thuc te, dung don thanh mot commit to.
 */
#include "hal_uart.h"
#include "bsp.h"

/* TODO Dev 3:
 *   1. hal_uart_init(): bat clock USART1, PA9 che do AF_PP, PA10 input float,
 *      BRR = APB2 / baudrate, CR1 = TE | RE | UE
 *   2. hal_uart_putc(): cho TXE roi ghi DR
 *   3. hal_uart_puts(): neu scheduler dang chay thi lay g_xUartMutex
 *      (timeout 50ms, that bai thi bo qua - KHONG block vinh vien),
 *      chua chay thi ghi thang
 *   4. hal_uart_log(): them tien to "[tick] " bang snprintf
 *
 * TEST: mo minicom hoac screen /dev/ttyUSB0 115200, thay chuoi khoi dong.
 */

/* ===== Than rong. Dev 3 dien vao. ===== */
void hal_uart_init(uint32_t baudrate) { (void) baudrate; }

void hal_uart_putc(char c) { (void) c; }

void hal_uart_puts(const char *str) { (void) str; }

void hal_uart_log(const char *str) { (void) str; }
