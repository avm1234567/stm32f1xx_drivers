#include "rcc.h"
#include "gpio.h"

int main()
{
    RCC_GPIOC_CLK_ENABLE();
    IO_Init(GPIOC, 13, GPIO_GP_PP_50MHz);

    while(1)
    {
        IO_TogglePin(GPIOC, 13);
        
        for(volatile uint32_t i = 0; i < 500000; i++);
    }
}