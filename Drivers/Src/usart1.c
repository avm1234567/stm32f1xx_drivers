#include "rcc.h"
#include "gpio.h"
#include "usart1.h"

void USART1_Init(void)
{
	RCC_GPIOA_CLK_ENABLE();

	RCC_USART1_CLK_ENABLE();

	IO_Init(GPIOA, 9, GPIO_AF_PP_50MHz);
	IO_Init(GPIOA, 10, GPIO_INPUT_FI);
	USART1->BRR = 0x45;// Baud Rate 115200

	USART1->CR1 |= USART1_CR1_UE; // USART enable
	USART1->CR1 |= USART1_CR1_TE; // Transmitter enable
	USART1->CR1 |= USART1_CR1_RE; // Receiver enable

}

void USART1_SendChar(char data)
{
	while(!(USART1->SR & USART1_SR_TXE));

	USART1->DR = data;
}

void USART1_SendString(char *str)
{
	while(*str)
	{
		USART1_SendChar(*str);
		str++;
	}
}

char USART1_ReceiveChar(void)
{
	while(!(USART1->SR & USART1_SR_RXNE));

	return USART1->DR;
}

void USART1_ReceiveString(char *buffer)
{
	char ch;

	while(1)
	{
		ch = USART1_ReceiveChar();

		if(ch == '\r')
		{
			break;
		}
		 *buffer = ch;
		 buffer++;
		}

	*buffer = '\0';
}

int USART1_StringToInt(char *str)
{
    int num = 0;

    while(*str)
    {
        num = num * 10 + (*str - '0');
        str++;
    }

    return num;
}

