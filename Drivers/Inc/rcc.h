#ifndef RCC_H
#define RCC_H

#include "stm32f103xx.h"

#define RCC_APB2ENR_IOPAEN (1 << 2)
#define RCC_APB2ENR_IOPBEN (1 << 3)
#define RCC_APB2ENR_IOPCEN (1 << 4)
#define RCC_APB2ENR_IOPDEN (1 << 5)
#define RCC_APB2ENR_IOPEEN (1 << 6)// Clock enable macros referred Table 18 PG.121

#define RCC_APB2ENR_AFIOEN (1 << 0)

#define RCC_APB2ENR_USART1EN (1 << 14)
#define RCC_APB2ENR_SPI1EN (1 << 12)

#define RCC_APB2ENR_ADC1EN      (1 << 9)
#define RCC_APB2ENR_ADC2EN      (1 << 10)

#define RCC_APB2ENR_TIM1EN      (1 << 11)


void RCC_GPIOA_CLK_ENABLE(void);
void RCC_GPIOB_CLK_ENABLE(void);
void RCC_GPIOC_CLK_ENABLE(void);
void RCC_GPIOD_CLK_ENABLE(void);
void RCC_GPIOE_CLK_ENABLE(void);

void RCC_USART1_CLK_ENABLE(void);

#endif
