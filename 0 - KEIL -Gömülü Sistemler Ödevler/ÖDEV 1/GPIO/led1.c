/*TM4C1294NCPDTI Hrdware connections 
The switches are connected to GPIO pins 
PJ0	USW1
PJ1	USW2
Four user LEDs are provided on the board. 
PN1	D1 
PN0	D2
PF4	D3	
PF0	D4	
 */
#include "TM4C129.h"                    // Device header
void ms_delay(int32_t ms);
int main(void)
{
   
   SYSCTL->RCGCGPIO |= (1<<12)|(1<<8)|(1<<5);   /* enable clock to GPIO N,J,F Ports */
  // GPIOJ_AHB->LOCK = 0x4C4F434B;   		// unlockGPIOCR register
   GPIOJ_AHB->PUR |= 0x3;        			// Enable Pull Up resistor PJ0 & PJ1
   GPIOF_AHB->DIR |= (1<<0)|(1<<4);   //set PF0 as an output and PF4 as an input pin
   GPIOF_AHB->DEN |= (1<<0)|(1<<4);   // Enable PF0 and PF4 as a digital GPIO pins 
   GPION->DIR |= (1<<0)|(1<<1);       //set PN0 as an output and PN1 as an input pin
   GPION->DEN |= (1<<0)|(1<<1);       // Enable PN0 and PN1 as a digital GPIO pins 

	while(1)
	{
		GPIOF_AHB->DATA |=(1<<0);		// LED is on
		GPIOF_AHB->DATA |=(1<<4);		// LED is on
		GPION->DATA |=(1<<0);				// LED is on
		GPION->DATA |=(1<<1);				// LED is on
		ms_delay(300);							// Wait 300 ms
		GPIOF_AHB->DATA &=~(1<<0);	// LED is off
		GPIOF_AHB->DATA &=~(1<<4);	// LED is off
		GPION->DATA &=~(1<<0);			// LED is off
		GPION->DATA &=~(1<<1);			// LED is off
		ms_delay(300);							// Wait 300 ms
	}
}
void ms_delay(int32_t ms)
{
	for(int i=0;i<ms;i++)
  {
		for(int j=0;j<3180;j++)
    {
			__NOP();
    }
  }
}