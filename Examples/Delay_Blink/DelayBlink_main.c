#include "rcc.h"
#include "gpio.h"
#include "tim2.h"

int main(void)
{
    RCC_GPIOC_CLK_ENABLE();
    IO_Init(GPIOC, 13, GPIO_GP_PP_2MHz);
    TIM2_Init();

    while(1)
    {
        IO_TogglePin(GPIOC, 13);
        TIM2_DelayMs(100);

    }

}
