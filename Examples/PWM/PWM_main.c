#include "tim2.h"

int main(void)
{
    TIM2_PWM_Init(7, 999); // Set prescaler to 7 and auto-reload value to 999 for a PWM frequency of 1 kHz
    TIM2_PWM_SetDutyCycle(25); // Set duty cycle to 25%
    while (1)
    {
      
    }
}