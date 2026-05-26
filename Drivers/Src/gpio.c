#include "gpio.h"



void IO_WritePin(GPIO_TypeDef *GPIOy, uint8_t PinNumber, uint8_t State)
{
    if(State == GPIO_PIN_SET)
    {
        GPIOy->ODR |= (1 << PinNumber);
    }
    else
    {
        GPIOy->ODR &= ~(1 << PinNumber);
    }
}

void IO_TogglePin(GPIO_TypeDef *GPIOy, uint8_t PinNumber)
{
	GPIOy->ODR ^= (1 << PinNumber);
}

uint8_t IO_ReadPin(GPIO_TypeDef *GPIOy, uint8_t PinNumber)
{
	return ((GPIOy->IDR >> PinNumber) & 0x1);
}

void IO_Init(GPIO_TypeDef *GPIOy, uint8_t PinNumber, uint8_t Mode)
{
	uint8_t position;

	if(PinNumber >= 8)
	{
		position = (PinNumber - 8) *4; //CRH for pin numbers 8-15
		GPIOy->CRH &= ~(0xF << position);
		GPIOy->CRH |= (Mode << position);
	}
	else{
		position = PinNumber * 4; //CRL for pin numbers 0-7
		GPIOy->CRL &= ~(0xF << position);
		GPIOy->CRL |= (Mode << position);
	}
}


