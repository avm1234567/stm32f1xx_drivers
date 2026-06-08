#include "rcc.h"
#include "gpio.h"
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

void TIM2_PWM_Init(uint16_t psc, uint16_t arr)
{
	RCC_GPIOA_CLK_ENABLE();
	RCC_TIM2_CLK_ENABLE();

	IO_Init(GPIOA, 0, GPIO_AF_PP_50MHz);

	TIM2->PSC = psc; 	// 8/(psc+1)

	TIM2->ARR = arr;

	TIM2->CCR1 = 0;		//initial duty cycle

	TIM2->CCMR1 &= ~TIM2_CCMR1_CC1S_Msk;
	TIM2->CCMR1 |= TIM2_CCMR1_CC1S_OC;		//CC1 channel configured as output

	TIM2->CCMR1 &= ~TIM2_CCMR1_OC1M_Msk;
	TIM2->CCMR1 |= TIM2_CCMR1_OC1M_PWM1;	//PWM mode 1

	TIM2->CCMR1 |= TIM2_CCMR1_OC1PE;		//Enable CCR1 preload
	TIM2->CR1   |= TIM2_CR1_ARPE;			//Enable ARR preload
	TIM2->EGR |= TIM2_EGR_UG;				//Update Event
	TIM2->CCER |= TIM2_CCER_CC1E;			// Channel output enable
	TIM2->CR1 |= TIM2_CR1_CEN;				//Counter Enable
}

void TIM2_PWM_SetDutyCycle(uint16_t duty)
{

	if(duty > 100)
	{
	    duty = 100;
	}
	TIM2->CCR1 = (duty * (TIM2->ARR+1))/100;


}

