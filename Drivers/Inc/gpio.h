#ifndef GPIO_H
#define GPIO_H

#include "stm32f103xx.h"

#define GPIO_PIN_0      0
#define GPIO_PIN_1      1
#define GPIO_PIN_2      2
#define GPIO_PIN_3      3
#define GPIO_PIN_4      4
#define GPIO_PIN_5      5
#define GPIO_PIN_6      6
#define GPIO_PIN_7      7
#define GPIO_PIN_8      8
#define GPIO_PIN_9      9
#define GPIO_PIN_10     10
#define GPIO_PIN_11     11
#define GPIO_PIN_12     12
#define GPIO_PIN_13     13
#define GPIO_PIN_14     14
#define GPIO_PIN_15     15

#define GPIO_PIN_RESET    0
#define GPIO_PIN_SET      1

// OUTPUT MODES
#define GPIO_GP_PP_10MHz 0x1 //General purpose push pull (0001)
#define GPIO_GP_PP_2MHz  0x2 //(0010) 00:CNF     10:MODE
#define GPIO_GP_PP_50MHz 0x3

#define GPIO_GP_OD_10MHz 0x5 //General purpose open drain
#define GPIO_GP_OD_2MHz  0x6
#define GPIO_GP_OD_50MHz 0x7

#define GPIO_AF_PP_10MHz 0x9 //Alternate function push pull
#define GPIO_AF_PP_2MHz  0xA
#define GPIO_AF_PP_50MHz 0xB

#define GPIO_AF_OD_10MHz 0xD //Alternate function open drain
#define GPIO_AF_OD_2MHz  0xE
#define GPIO_AF_OD_50MHz 0xF

//INPUT MODES
#define GPIO_INPUT_AM 0x0 //Analog mode
#define GPIO_INPUT_FI 0X4 //Floating Input
#define GPIO_INPUT_PUPD 0x8 //Input with Pull up / Pull Down
//#define GPIO_INPUT_RESV 0xC // Reserved

void IO_WritePin(GPIO_TypeDef *GPIOy, uint8_t PinNumber, uint8_t State);
void IO_TogglePin(GPIO_TypeDef *GPIOy, uint8_t PinNumber);
uint8_t IO_ReadPin(GPIO_TypeDef *GPIOy, uint8_t PinNumber);
void IO_Init(GPIO_TypeDef *GPIOy, uint8_t PinNumber, uint8_t Mode);


#endif
