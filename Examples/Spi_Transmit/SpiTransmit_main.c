#include "usart1.h"
#include "spi1.h"

int main()
{
    USART1_Init();
    SPI1_Init();

    uint8_t data;

    while(1)
    {
        data = SPI1_TransferReceiveByte('A');

        if(data == 'A')
        {
            USART1_SendString("Received :");
            USART1_SendChar(data);
            USART1_SendString("\r\n");
        }
        
        for(volatile uint32_t i = 0; i < 500000; i++);
    }

}