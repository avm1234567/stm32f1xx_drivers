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

void TIM2_Init(void);
void TIM2_DelayMs(uint16_t ms);

#endif
