#include "usart.h"

int main{
    USART1_Init();
    while(1)
    {
        USART1_SendChar('A');

        USART1_SendString("\n\rHello World!");

        for(volatile uint32_t i = 0; i < 500000; i++);

    }
}