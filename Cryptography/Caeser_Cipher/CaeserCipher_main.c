#include "rcc.h"
#include "gpio.h"
#include "usart1.h"

void Caeser_Encryption(char *data)
{

	while(*data)
	{
		if(*data != ' '){
			*data = *data + 3;
		}
		data++;
	}
}


int main(void)
{

    USART1_Init();
    char msg[50];


    while(1)
    {


    	
    	USART1_ReceiveString(msg);
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");
		Caeser_Encryption(msg);
		USART1_SendString("CipherText:");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");

    }
}
