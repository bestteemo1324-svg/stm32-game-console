/**
 * @file  bsp.c
 * @brief Khoi tao xung nhip 72MHz tu HSE 8MHz.
 * @owner LEADER
 */
#include "bsp.h"

void bsp_system_init(void)
{
    /* 1. Bat HSE, cho on dinh */
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0U) { }

    /* 2. Flash 2 wait-state cho SYSCLK > 48MHz, bat prefetch */
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    /* 3. AHB=1 (72M), APB1=2 (36M), APB2=1 (72M), ADC=6 (12MHz) */
    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2 | RCC_CFGR_ADCPRE);
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2
               | RCC_CFGR_PPRE2_DIV1 | RCC_CFGR_ADCPRE_DIV6;

    /* 4. PLL: HSE x9 = 72MHz */
    RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9;

    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0U) { }

    /* 5. Chuyen SYSCLK sang PLL */
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) { }

    SystemCoreClock = BSP_SYSCLK_HZ;

    /* 6. Clock cho GPIO dung chung */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN
                  | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;

    /* 7. 4 bit preempt, 0 bit sub - bat buoc cho FreeRTOS */
    NVIC_SetPriorityGrouping(3U);
}

void bsp_delay_ms_blocking(uint32_t ms)
{
    for (uint32_t i = 0U; i < ms; i++) {
        for (volatile uint32_t j = 0U; j < 7200U; j++) { }
    }
}
