#include "rcc.h"
#include "tim2.h"

void TIM2_Init(void)
{
	RCC_TIM2_CLK_ENABLE();

	TIM2->PSC = 7999;

	TIM2->EGR |= TIM2_EGR_UG;
}

void TIM2_DelayMs(uint16_t ms)
{
	TIM2->ARR = ms - 1;
	TIM2->CNT = 0;
	TIM2->SR &= ~TIM2_SR_UIF;
	TIM2->CR1 |= TIM2_CR1_CEN;
	while(!(TIM2->SR & TIM2_SR_UIF));
	TIM2->CR1 &= ~TIM2_CR1_CEN;
}
