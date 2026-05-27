#ifndef USART1_H
#define USART1_H

#include "stm32f103xx.h"

#define USART1_CR1_UE (1 << 13) // USART enable
#define USART1_CR1_TE (1 << 3) // Transmitter enable
#define USART1_CR1_RE (1 << 2) // Receiver enable

#define USART1_SR_TXE (1 << 7)
#define USART1_SR_RXNE (1 << 5)

void USART1_Init(void);
void USART1_SendChar(char data);
void USART1_SendString(char *str);
char USART1_ReceiveChar(void);
void USART1_ReceiveString(char *buffer);

#endif
