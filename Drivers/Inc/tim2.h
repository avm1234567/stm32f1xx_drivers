#ifndef TIM2_H
#define TIM2_H

#include "stm32f103xx.h"

#define TIM2_CR1_CKD_0 	(1 << 8)
#define TIM2_CR1_CKD_1 	(1 << 9)
#define TIM2_CR1_ARPE 	(1 << 7)
#define TIM2_CR1_CMS_0 	(1 << 5)
#define TIM2_CR1_CMS_1	(1 << 6)
#define TIM2_CR1_DIR 	(1 << 4)
#define TIM2_CR1_OPM 	(1 << 3)
#define TIM2_CR1_URS 	(1 << 2)
#define TIM2_CR1_UDIS	(1 << 1)
#define TIM2_CR1_CEN	(1 << 0)

#define TIM2_DIER_UIE (1 << 0)

#define TIM2_SR_UIF (1 << 0)

#define TIM2_EGR_UG (1 << 0)

#define TIM2_CCMR1_CC1S_OC (0 << 0)		//Output mode
#define TIM2_CCMR1_CC1S_IPTR1 (1 << 0) 	//INPUT mode IC1 mapped on TI1
#define TIM2_CCMR1_CC1S_IPTR2 (2 << 0)	//INPUT mode IC1 mapped on TI2
#define TIM2_CCMR1_CC1S_IPTRC (3 << 0)	//INPUT mode IC1 mapped on TRC
#define TIM2_CCMR1_CC1S_Msk   (3 << 0)
#define TIM2_CCMR1_OC1M_Msk   (7 << 4)
#define TIM2_CCMR1_OC1M_PWM1 (6 << 4) 	//PWM mode 1
#define TIM2_CCMR1_OC1M_PWM2 (7 << 4)	//PWM mode 2
#define TIM2_CCMR1_OC1PE (1 << 3)

#define TIM2_CCER_CC1E (1 << 0)


void TIM2_Init(void);
void TIM2_DelayMs(uint16_t ms);
void TIM2_PWM_Init(uint16_t psc, uint16_t arr);
void TIM2_PWM_SetDutyCycle(uint16_t duty);

#endif
