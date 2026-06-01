#ifndef SPI1_H
#define SPI1_H

#include "stm32f103xx.h"

#define SPI1_CR1_SPE (1 << 6)

#define SPI1_CR1_CPHA      (1 << 0)
#define SPI1_CR1_CPOL      (1 << 1)
#define SPI1_CR1_MSTR      (1 << 2)

#define SPI1_CR1_BR_0      (1 << 3)
#define SPI1_CR1_BR_1      (1 << 4)
#define SPI1_CR1_BR_2      (1 << 5)

#define SPI1_CR1_LSBFIRST  (1 << 7)

#define SPI1_CR1_SSI       (1 << 8)
#define SPI1_CR1_SSM       (1 << 9)

#define SPI1_CR1_RXONLY    (1 << 10)

#define SPI1_CR1_DFF       (1 << 11)


#define SPI1_SR_TXE (1 << 1)
#define SPI1_SR_RXNE (1 << 0)

#define SPI1_SR_BSY (1 << 7)

void SPI1_Init(void);
void SPI1_SendByte(char data);
uint8_t SPI1_TransferReceiveByte(uint8_t data);
uint8_t SPI1_ReceiveByte(void);
void SPI1_SendString(uint8_t *str);
void SPI1_CS_Enable(void);
void SPI1_CS_Disable(void);

#endif
