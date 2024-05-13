/* Blink the LED available on the Tiva C TM4C123G launchpad using timer0 with timer0 interrupt*/

#include "TM4C123.h"                    // Device header
#define LED_RED   (1U << 1)
void Timer0_Init(void);
void LED_init(void);

int main()
{
  LED_init();
	Timer0_Init(); 
	while(1)
    {
    }
}
void LED_init(){
	SYSCTL->RCGCGPIO |= (1U << 5);  // enable clock for GPIOF
  GPIOF->DEN |= LED_RED; // enable digital function on pin 1
  GPIOF->DIR |= LED_RED; // set pin 1 as output
}
void Timer0_Init(void) {
    // Enable Timer0 clock
    SYSCTL->RCGCTIMER |= (1U << 0);
    TIMER0->CTL &= ~(1U << 0);		// Disable Timer0
    TIMER0->CFG = 0x00000000; 		// 32-bit mode
    TIMER0->TAMR = 0x00000002; 		// Periodic mode
    TIMER0->TAILR = (16000000 / 2) - 1;  //500 ms
    TIMER0->IMR |= (1U << 0); 		// Enable Timer0 interrupt
    NVIC_EnableIRQ(TIMER0A_IRQn);	// Enable the NVIC interrupt for Timer0
    TIMER0->CTL |= (1U << 0);			// Enable Timer0
}
void TIMER0A_Handler(void) {
    GPIOF->DATA ^= LED_RED;
    // Clear the Timer0 interrupt flag
    TIMER0->ICR |= (1U << 0);
}