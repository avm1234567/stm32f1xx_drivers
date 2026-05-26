#ifndef STM32F103XX_H
#define STM32F103XX_H

#include <stdint.h>

#define PERIPHERAL_BASE 0x40000000UL
#define APB2PERIPH_BASE (PERIPHERAL_BASE + 0x10000UL)
#define AHBPERIPH_BASE  (PERIPHERAL_BASE + 0x18000UL) //Referred Table 3 Of manual RM0008 PG.50,51,52

//RCC
#define RCC_BASE (AHBPERIPH_BASE + 0x9000) // Referred Table 3 on PG.50

typedef struct
{
    volatile uint32_t CR;          // 0x00
    volatile uint32_t CFGR;        // 0x04
    volatile uint32_t CIR;         // 0x08
    volatile uint32_t APB2RSTR;    // 0x0C
    volatile uint32_t APB1RSTR;    // 0x10
    volatile uint32_t AHBENR;      // 0x14
    volatile uint32_t APB2ENR;     // 0x18
    volatile uint32_t APB1ENR;     // 0x1C
    volatile uint32_t BDCR;        // 0x20
    volatile uint32_t CSR;         // 0x24

} RCC_TypeDef;// Referred Table 18 of manual PG.121

#define RCC ((RCC_TypeDef*) RCC_BASE)

//GPIO
#define GPIOA_BASE (APB2PERIPH_BASE + 0x800UL)
#define GPIOB_BASE (APB2PERIPH_BASE + 0xC00UL)
#define GPIOC_BASE (APB2PERIPH_BASE + 0x1000UL)
#define GPIOD_BASE (APB2PERIPH_BASE + 0x1400UL)
#define GPIOE_BASE (APB2PERIPH_BASE + 0x1800UL)

typedef struct
{
	volatile uint32_t CRL; //0x00
	volatile uint32_t CRH; //0x04
	volatile uint32_t IDR; //0x08
	volatile uint32_t ODR; //0x0C
	volatile uint32_t BSRR; //0x10
	volatile uint32_t BRR; //0x14
	volatile uint32_t LCKR; //0x18
} GPIO_TypeDef;

#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef*) GPIOE_BASE)

//USART
#define USART1_BASE (APB2PERIPH_BASE + 0x3800)

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART1_TypeDef;

#define USART1 ((USART1_TypeDef*) USART1_BASE)

#endif

