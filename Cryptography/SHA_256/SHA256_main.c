#include <stdio.h>
#include "usart1.h"
#include <string.h>

const uint32_t K[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,

    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,

    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,

    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t ROTR(uint32_t x, uint8_t n){
	return ((x >> n) | (x << (32 - n)));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
	return((x & y) ^ (~x & z));
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
	return ((x & y) ^ (x & z) ^ (y & z));
}

uint32_t E0(uint32_t x){
	return (ROTR(x,2) ^ ROTR(x,13) ^ ROTR(x,22));
}

uint32_t E1(uint32_t x){
	return (ROTR(x,6) ^ ROTR(x,11) ^ ROTR(x,25));
}

uint32_t Sig0(uint32_t x){
	return (ROTR(x,7) ^ ROTR(x,18) ^ (x >> 3));
}

uint32_t Sig1(uint32_t x){
	return (ROTR(x,17) ^ ROTR(x,19) ^ (x >> 10));
}

void SHA256_PadMessage(uint8_t *msg, uint8_t len, uint8_t *pad){
	memcpy(pad,msg,len);
	pad[len] = 0x80;
	for(int i = len+1; i <= 55;i++){
		pad[i] = 0x00;
	}
	uint64_t bit_len = (uint64_t)len * 8;
	for(int j = 0;j<8; j++){
		pad[63-j] = (uint8_t)(bit_len >> (8 * j));
	}
}

int main(void)
{
    USART1_Init();

        char msg[64];
    uint8_t cikey[64];
    char retmsg[64];

    while(1){
        USART1_SendString("Enter PlainText:");
    	USART1_ReceiveString(msg);
       	USART1_SendString("\r\n");
       	USART1_SendString(msg);

       	SHA256_PadMessage((uint8_t *)msg,strlen(msg),cikey);
       	USART1_SendString("\r\n");
       	for(int i=0;i<64;i++)
       	{
       		sprintf(retmsg,"%02X",cikey[i]);
       		USART1_SendString(retmsg);
       		if((i + 1) % 16 == 0)
       		{
       		    USART1_SendString("\r\n");
       		}
       	}
       	USART1_SendString("\r\n");
    }
}