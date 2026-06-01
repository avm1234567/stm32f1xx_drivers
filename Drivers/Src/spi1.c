#include "rcc.h"
#include "gpio.h"
#include "spi1.h"

void SPI1_Init(void)
{
	RCC_GPIOA_CLK_ENABLE();

	RCC_SPI1_CLK_ENABLE();

	IO_Init(GPIOA, 5, GPIO_AF_PP_50MHz); //SCK
	IO_Init(GPIOA, 6, GPIO_INPUT_FI); //MISO
	IO_Init(GPIOA, 7, GPIO_AF_PP_50MHz); //MOSI
	IO_Init(GPIOA, 4, GPIO_GP_PP_50MHz); //NSS/CS

	IO_WritePin(GPIOA, 4, GPIO_PIN_SET);



	SPI1->CR1 |= SPI1_CR1_MSTR; //Master Configuration
	SPI1->CR1 != SPI1_CR1_SSM; //Software Slave management enabled
	SPI1->CR1 |= SPI1_CR1_SSI; //Internal Slave Select
	SPI1->CR1 |= SPI1_CR1_BR_0; //Baud Rate
	SPI1->CR1 |= SPI1_CR1_SPE; //SPI Enable

}

void SPI1_SendByte(char data)
{
	while(!(SPI1->SR & SPI1_SR_TXE));

	SPI1->DR = data;

	while(!(SPI1->SR & SPI1_SR_RXNE));

	volatile uint8_t dummy = SPI1->DR;

	while(SPI1->SR & SPI1_SR_BSY);
}

uint8_t SPI1_TransferReceiveByte(uint8_t data)
{
	while(!(SPI1->SR & SPI1_SR_TXE));

	SPI1->DR = data;

	while(!(SPI1->SR & SPI1_SR_RXNE));

	return SPI1->DR;
}

uint8_t SPI1_ReceiveByte(void)
{

    while(!(SPI1->SR & SPI1_SR_TXE));

    SPI1->DR = 0xFF;

	while(!(SPI1->SR & SPI1_SR_RXNE));

	while(SPI1->SR & SPI1_SR_BSY);

	return SPI1->DR;

}

void SPI1_SendString(uint8_t *str)
{
	while(*str)
	{
		SPI1_SendByte(*str);
		str++;
	}
}

void SPI1_CS_Enable(void)
{
    IO_WritePin(GPIOA, 4, GPIO_PIN_RESET);
}

void SPI1_CS_Disable(void)
{
    IO_WritePin(GPIOA, 4, GPIO_PIN_SET);
}
