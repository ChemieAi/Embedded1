/* SysTick zamanlayicisini kesmeli 1 saniye zaman geciktirme i�in kullan */
#include "TM4C123.h"                    // Device header
#define LED_RED   (1U << 1)

void SysTick_Handler(void);

int main()
{
	  __disable_irq(); 							// ayarlama i�in global kesmeyi kapat
    SYSCTL->RCGCGPIO |= (1U << 5);  // GPIOF izinle
    GPIOF->DEN |= LED_RED; 					// pin 1 digital 
    GPIOF->DIR |= LED_RED; 					// pin 1 �ikis
    SysTick->LOAD = 16000000 - 1; 	// 1 saniye i�in yeniden y�kleme degerini belirle
    SysTick->VAL = 0; 							// baslangi� i�in sifirla
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U; // systick timer izinle, sistem saatini kullansin kesme izinlendi.
    __enable_irq(); // enable global interrupts
    while(1)
    {
        
    }
}

void SysTick_Handler(void)
{
    GPIOF->DATA ^= LED_RED; // toggle LED pin
}