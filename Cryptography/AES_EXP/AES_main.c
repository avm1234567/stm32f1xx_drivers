#include <stdio.h>
#include "usart1.h"

uint8_t state[4][4];
uint8_t key[4][4];
uint8_t words[44][4]; 

const uint8_t sbox[256] = //Substitution box
{
0x63,0x7C,0x77,0x7B,0xF2,0x6B,0x6F,0xC5,0x30,0x01,0x67,0x2B,0xFE,0xD7,0xAB,0x76,
0xCA,0x82,0xC9,0x7D,0xFA,0x59,0x47,0xF0,0xAD,0xD4,0xA2,0xAF,0x9C,0xA4,0x72,0xC0,
0xB7,0xFD,0x93,0x26,0x36,0x3F,0xF7,0xCC,0x34,0xA5,0xE5,0xF1,0x71,0xD8,0x31,0x15,
0x04,0xC7,0x23,0xC3,0x18,0x96,0x05,0x9A,0x07,0x12,0x80,0xE2,0xEB,0x27,0xB2,0x75,
0x09,0x83,0x2C,0x1A,0x1B,0x6E,0x5A,0xA0,0x52,0x3B,0xD6,0xB3,0x29,0xE3,0x2F,0x84,
0x53,0xD1,0x00,0xED,0x20,0xFC,0xB1,0x5B,0x6A,0xCB,0xBE,0x39,0x4A,0x4C,0x58,0xCF,
0xD0,0xEF,0xAA,0xFB,0x43,0x4D,0x33,0x85,0x45,0xF9,0x02,0x7F,0x50,0x3C,0x9F,0xA8,
0x51,0xA3,0x40,0x8F,0x92,0x9D,0x38,0xF5,0xBC,0xB6,0xDA,0x21,0x10,0xFF,0xF3,0xD2,
0xCD,0x0C,0x13,0xEC,0x5F,0x97,0x44,0x17,0xC4,0xA7,0x7E,0x3D,0x64,0x5D,0x19,0x73,
0x60,0x81,0x4F,0xDC,0x22,0x2A,0x90,0x88,0x46,0xEE,0xB8,0x14,0xDE,0x5E,0x0B,0xDB,
0xE0,0x32,0x3A,0x0A,0x49,0x06,0x24,0x5C,0xC2,0xD3,0xAC,0x62,0x91,0x95,0xE4,0x79,
0xE7,0xC8,0x37,0x6D,0x8D,0xD5,0x4E,0xA9,0x6C,0x56,0xF4,0xEA,0x65,0x7A,0xAE,0x08,
0xBA,0x78,0x25,0x2E,0x1C,0xA6,0xB4,0xC6,0xE8,0xDD,0x74,0x1F,0x4B,0xBD,0x8B,0x8A,
0x70,0x3E,0xB5,0x66,0x48,0x03,0xF6,0x0E,0x61,0x35,0x57,0xB9,0x86,0xC1,0x1D,0x9E,
0xE1,0xF8,0x98,0x11,0x69,0xD9,0x8E,0x94,0x9B,0x1E,0x87,0xE9,0xCE,0x55,0x28,0xDF,
0x8C,0xA1,0x89,0x0D,0xBF,0xE6,0x42,0x68,0x41,0x99,0x2D,0x0F,0xB0,0x54,0xBB,0x16
};

//STATE

void AES_State(uint8_t *input){
	int k = 0;
	 for(int col = 0;col < 4; col++){
		 for(int row = 0;row < 4; row++){
			 state[row][col] = input[k];
			 k++;
		 }
	 }
}

void AES_PrintState(void){
    char buffer[10];
    for(int row = 0; row < 4; row++)
    {
    	for(int col = 0; col < 4; col++)
        {
            sprintf(buffer,"%02X ",state[row][col]);
            USART1_SendString(buffer);
        }
        USART1_SendString("\r\n");
    }
}

//KEY

void AES_Key(uint8_t *input){
	int k = 0;
	 for(int col = 0;col < 4; col++){
		 for(int row = 0;row < 4; row++){
			 key[row][col] = input[k];
			 k++;
		 }
	 }
}

void AES_PrintKey(void){
    char buffer[10];
    for(int row = 0; row < 4; row++)
    {
    	for(int col = 0; col < 4; col++)
        {
            sprintf(buffer,"%02X ",key[row][col]);
            USART1_SendString(buffer);
        }
        USART1_SendString("\r\n");
    }
}

//ADD ROUND KEY

void AES_AddRoundKey(uint8_t round){

	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			state[row][col] ^= words[(round* 4)+ col][row];
		}
	}
}

//SUBSTITUTE BYTES

void AES_SubsByte(void){
	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			state[row][col] = sbox[state[row][col]];
		}
	}
}

//SHIFT ROWS

void AES_ShiftRows(void){
for(int row = 1; row < 4; row++){

	for(int x = 0; x < row; x++){
		uint8_t temp = state[row][0];
		state[row][0] = state[row][1];
		state[row][1] = state[row][2];
		state[row][2] = state[row][3];
		state[row][3] = temp;
	}
}
}

//MIX COLUMNS

uint8_t AES_Mul2(uint8_t x)
{
	if(x & 0x80){ //check if the bit is set
		return (x << 1) ^ 0x1B; 
	}
	else{
		return (x << 1);
	}
}

uint8_t GF_Mul(uint8_t x,uint8_t mul){
	switch(mul)
	{
		case 0x01:
			return x;
		case 0x02:
			return AES_Mul2(x);
		case 0x03:
			return AES_Mul2(x) ^ x;
		case 0x09:
			return AES_Mul2(AES_Mul2(AES_Mul2(x))) ^ x;
		case 0x0B:
			return AES_Mul2(AES_Mul2(AES_Mul2(x))) ^ AES_Mul2(x) ^ x;
		case 0x0D:
			return AES_Mul2(AES_Mul2(AES_Mul2(x))) ^ AES_Mul2(AES_Mul2(x)) ^ x;
		case 0x0E:
			return AES_Mul2(AES_Mul2(AES_Mul2(x))) ^ AES_Mul2(AES_Mul2(x)) ^ AES_Mul2(x);
		default:
			return 0;
	}
}


void AES_MixCol(void){
	for(int col = 0;col < 4;col++){
		uint8_t s0 = state[0][col];
		uint8_t s1 = state[1][col];
		uint8_t s2 = state[2][col];
		uint8_t s3 = state[3][col];

        state[0][col] = GF_Mul(s0,0x02) ^ GF_Mul(s1,0x03) ^ s2 ^ s3;

        state[1][col] = s0 ^ GF_Mul(s1,0x02) ^ GF_Mul(s2,0x03) ^ s3;

        state[2][col] = s0 ^ s1 ^ GF_Mul(s2,0x02) ^ GF_Mul(s3,0x03);

        state[3][col] = GF_Mul(s0,0x03) ^ s1 ^ s2 ^ GF_Mul(s3,0x02);
	}
}

//KEY EXPANSION

	static uint8_t rcon_index = 0;
	const uint8_t Rcon[10] =  //Round constants
	{
	    0x01,
	    0x02,
	    0x04,
	    0x08,
	    0x10,
	    0x20,
	    0x40,
	    0x80,
	    0x1B,
	    0x36
	};

void AES_RotWord(uint8_t *word){

    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

void AES_SubsWord(uint8_t *word){
	for(int i = 0;i < 4;i++){
		word[i] = sbox[word[i]] ;
	}
}

void AES_KeyExpansion(void){
	for(int row=0;row<4;row++){
		 words[0][row] = key[row][0];
		 words[1][row] = key[row][1];
		 words[2][row] = key[row][2];
		 words[3][row] = key[row][3];
	}

	for(int j=3;j < 43;j++){
		if((j+1) % 4 == 0){
			uint8_t temp[4];
			for(int k=0;k<4;k++){
				temp[k] = words[j][k];
			}
			AES_RotWord(temp);
			AES_SubsWord(temp);
			temp[0] ^= Rcon[rcon_index];
			rcon_index++;
			for(int l=0;l<4;l++){
				words[j+1][l]= words[j-3][l] ^ temp[l];
			}

		}
		else{
			for(int m=0;m<4;m++)
			words[j+1][m]= words[j-3][m] ^ words[j][m];
		}
	}
}

int main(){
    USART1_Init();
    char msg[50];
    char cikey[50]; 

    while(1){
       USART1_SendString("Enter PlainText:");
    	USART1_ReceiveString(msg);
       	USART1_SendString("\r\n");
       	USART1_SendString(msg);
       	USART1_SendString("\r\n");
       	AES_State((uint8_t *)msg);
       	AES_PrintState();
       	USART1_SendString("\r\n");

       	USART1_SendString("Enter Key:");
       	USART1_ReceiveString(cikey);
       	USART1_SendString("\r\n");
       	USART1_SendString(cikey);
       	USART1_SendString("\r\n");
       	AES_Key((uint8_t *)cikey);
       	AES_PrintKey();
       	USART1_SendString("\r\n");

       	USART1_SendString("Key Expansion called done");
       	AES_KeyExpansion();
       	USART1_SendString("\r\n");

       	AES_AddRoundKey(0); //Initial Round 
       	USART1_SendString("Round 0:");
       	USART1_SendString("\r\n");
       	AES_PrintState();
       	USART1_SendString("\r\n");

        for(int round = 1;round<10;round++){ //Rounds 1-9
       		AES_SubsByte();
       		AES_ShiftRows();
       		AES_MixCol();
       		AES_AddRoundKey(round);
       	}

       	AES_SubsByte();
       	AES_ShiftRows();
       	AES_AddRoundKey(10);//Final Round

       	USART1_SendString("Final State:"); //Print Final State or Cipher Text
       	USART1_SendString("\r\n");
       	AES_PrintState();

    }
}