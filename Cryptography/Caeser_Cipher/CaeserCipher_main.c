#include "rcc.h"
#include "gpio.h"
#include "usart1.h"

void Caeser_Encryption(char *data , int key)
{

	while(*data)
	{
		if(*data != ' '){
			*data = *data + key;
		}
		data++;
	}
}

void Caeser_Decryption(char *data, int key)
{
	while(*data)
	{
		if(*data != ' ')
		{
			*data = *data - key;
		}
		data++;
	}
}

int main(void)
{

    USART1_Init();
	char msg[50];
	char cipherkey[10];
	int Ckey;


    while(1)
    {


    	
		USART1_SendString("Enter PlainText:");
    	USART1_ReceiveString(msg);
       	USART1_SendString("\r\n");
		USART1_SendString("Enter Key:");
    	USART1_ReceiveString(cipherkey);
    	Ckey = USART1_StringToInt(cipherkey);
    	USART1_SendString("\r\n");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");
    	USART1_SendString(cipherkey);
    	USART1_SendString("\r\n");
		Caeser_Encryption(msg, Ckey);
		USART1_SendString("CipherText:");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");
    	Caeser_Decryption(msg, Ckey);
		USART1_SendString("PlainText:");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");

    }
}
