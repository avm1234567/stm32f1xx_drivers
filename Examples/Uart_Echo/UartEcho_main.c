#include"usart1.h"

int main()
{
    USART1_Init();

    char msg[50];

    while(1)
    {
        USART1_ReceiveString(msg);
        USART1_SendString("Received:");
        USART1_SendString(msg);
        USART1_SendString("\r\n");
        for(volatile uint32_t i = 0; i < 500000; i++);
    }
}