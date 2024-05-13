/* SysTick zamanlayicisini kesmeli 1 saniye zaman geciktirme için kullan */
#include "TM4C123.h"                    // Device header
#define LED_RED   (1U << 1)

void SysTick_Handler(void);

int main()
{
	  __disable_irq(); 							// ayarlama için global kesmeyi kapat
    SYSCTL->RCGCGPIO |= (1U << 5);  // GPIOF izinle
    GPIOF->DEN |= LED_RED; 					// pin 1 digital 
    GPIOF->DIR |= LED_RED; 					// pin 1 çikis
    SysTick->LOAD = 16000000 - 1; 	// 1 saniye için yeniden yükleme degerini belirle
    SysTick->VAL = 0; 							// baslangiç için sifirla
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