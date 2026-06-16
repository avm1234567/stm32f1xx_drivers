#include <stdio.h>
#include "usart1.h"
#include <stdlib.h>


uint32_t p = 13;	//Prime factor 1
uint32_t q = 17;	//Prime factor 2
uint32_t n;
uint32_t e;		//Public exponent
uint32_t d;		//Private exponent
uint32_t phi_n;

uint32_t RSA_Modulus(uint32_t base,uint32_t exp, uint32_t mod){
	uint32_t result = 1;
	for(uint32_t i=0; i<exp;i++){
		result = result * base % mod; //formula for Encrypt: (M^e) % n and Decrypt: (C^d) % n
	}
	return result;
}

uint32_t GCD(int a,int b)
{
	while(b != 0){
		int temp = b;       //used to find greatest common divisor between e and phi_n is 1
		b = a % b;
		a = temp;
	}
	return a;
}

void RSA_Calculate(void){

	n = p*q;

	phi_n = ((p-1)*(q-1));
	while(1){
		e = rand() % (phi_n - 2) + 2;
		if(GCD(e,phi_n)==1){
			break;
		}
	}
    for(d = 2;d<phi_n;d++)
    {
        if(((d * e) % phi_n) == 1)
        {
            break;
        }
    }
		
}

uint32_t RSA_Encrypt(uint32_t M)
{
    uint32_t C;
    C = RSA_Modulus(M,e,n);
    return C;
}

uint32_t RSA_Decrypt(uint32_t C)
{
    uint32_t M;
    M = RSA_Modulus(C,d,n);
    return M; 
}

void RSA_EncryptString(char *msg, uint32_t *cipher)
{
    int i = 0;
    while(msg[i] != '\0')
    {
        cipher[i] = RSA_Encrypt(msg[i]);
        i++;
    }
    cipher[i] = '\0';
}

void RSA_DecryptString(uint32_t *cipher, char *msg)
{
    int i = 0;

    while(cipher[i] != '\0')
    {
        msg[i] = (char)RSA_Decrypt(cipher[i]);
        i++;
    }

    msg[i] = '\0';
}

int main()
{
    USART1_Init();
    srand(1234);
    while (1)
    {
        RSA_Calculate();

        USART1_SendString("Enter Plaintext");
        USART1_ReceiveString(msg);
       	USART1_SendString("\r\n");
       	sprintf(buf,"%lu",e);
       	USART1_SendString(buf);
        USART1_SendString("\r\n");
        USART1_SendString(msg);
        RSA_EncryptString(msg,cipher);
    	USART1_SendString("\r\n");
        USART1_SendString("CipherText:");
		for(int i = 0; msg[i] != '\0'; i++)
		{
		    sprintf(buffer, "%lu ", cipher[i]);
		    USART1_SendString(buffer);
		}
        USART1_SendString("\r\n");
    	RSA_DecryptString(cipher,msg);
		USART1_SendString("PlainText:");
    	USART1_SendString(msg);
    	USART1_SendString("\r\n");
    }
    
    
}