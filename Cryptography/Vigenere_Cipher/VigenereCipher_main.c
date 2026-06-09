#include "usart1.h"

void Vigenere_Cipher(char *data, char *key)
{
	int i = 0;
	int j = 0;
	while(data[i])
	{

		if(data[i]>='A' && data[i]<='Z' && key[j]>='A' && key[j]<='Z') //UPPERCASE
		{
			data[i] = ((data[i]-'A')+(key[j]-'A')) % 26 + 'A';

			j++;

			if(key[j] == '\0')
			{
				j=0;
			}

		}
		else															//lowercase
		{
			data[i] = ((data[i]-'a')+(key[j]-'a')) % 26 + 'a';

			j++;

			if(key[j] == '\0')
			{
				j=0;
			}

		}

		i++;
	}
}

int main(void)
{
    USART1_Init();

    char msg[50];
    char cipherkey[20];

    while(1)
    {
     	USART1_SendString("Enter PlainText:");
    	USART1_ReceiveString(msg);
       	USART1_SendString("\r\n");
		USART1_SendString("Enter Key:");
    	USART1_ReceiveString(cipherkey);
    	USART1_SendString("\r\n");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");
    	USART1_SendString(cipherkey);
    	USART1_SendString("\r\n");
    	Vigenere_Cipher(msg, cipherkey);
		USART1_SendString("CipherText:");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");   
    }
}