/* Blink the LED available on the Tiva C TM4C123G launchpad using timer0 */
#include "TM4C123.h"                    // Device header
#define LED_RED   (1U << 1)
void timer0_init(void);
void led_init(void);

int main()
{
  led_init();
	timer0_init(); 
	while(1)
        {
	  GPIOF->DATA ^= LED_RED;
          while(!(TIMER0->RIS & 1U)); 	// timer0 overflow için bekle
          TIMER0->ICR = 1U; 						// timer0 interrupt flag'i temizle
    }
}
void led_init(){
	SYSCTL->RCGCGPIO |= (1U << 5);  // enable clock for GPIOF
  GPIOF->DEN |= LED_RED; 					// pin 1 digital  
  GPIOF->DIR |= LED_RED; 					// pin 1 çikis
}
void timer0_init(void)
{
    SYSCTL->RCGCTIMER |= (1U << 0); // Timer0 saatini izinle
    TIMER0->CTL = 0; 								// disable timer0
    TIMER0->CFG = 0; 								// select 32-bit mode
    TIMER0->TAMR = 0x02; 						// select periodic mode		
    TIMER0->TAILR = 16000000 - 1; 	// 1 saniye için deger belirle
	  TIMER0->CTL |= (1U << 0); 			// enable timer0
}
