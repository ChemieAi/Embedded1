/*TM4C1294NCPDTI Hrdware connections 
The switches are connected to GPIO pins 
PJ0	USW1
PJ1	USW2
Four user LEDs are provided on the board. 
PN1	D1 
PN0	D2
PF4	D3	
PF0	D4	
Never use these pins
PC[3:0] JTAG/SWD
PD7
PE7
 */
#include "TM4C129.h"                    // Device header
void ms_delay(int32_t ms);
int main(void)
{
   unsigned int state;
   SYSCTL->RCGCGPIO |= (1<<12)|(1<<8)|(1<<5);   /* enable clock to GPIO N,J,F Ports */
  // GPIOJ_AHB->LOCK = 0x4C4F434B;   		// unlockGPIOCR register
   GPIOJ_AHB->PUR |= 0x3;        			// Enable Pull Up resistor PJ0 & PJ1
   GPIOF_AHB->DIR |= (1<<0)|(1<<4);   //set PF0 as an output and PF4 as an input pin
   GPIOF_AHB->DEN |= (1<<0)|(1<<4);   // Enable PF0 and PF4 as a digital GPIO pins 
   GPION->DIR |= (1<<0)|(1<<1);       //set PN0 as an output and PN1 as an input pin
   GPION->DEN |= (1<<0)|(1<<1);       // Enable PN0 and PN1 as a digital GPIO pins 
	 GPIOJ_AHB->DEN |= (1<<0)|(1<<1);       // Enable PJ0 and PJ1 as a digital GPIO pins 
		
		GPIOF_AHB->DATA &=~((1<<0)|(1<<4));	// D3 & D4 LEDs are off
		GPION->DATA &=~((1<<0)|(1<<1));			// D1 & D2 LEDs are off

	while(1)
	{
		if(!(GPIOJ_AHB->DATA & 0x1))
		{
			ms_delay(200);							// Wait 300 ms
			GPIOF_AHB->DATA ^=(1<<0);		// LED D4 is toggling wiith push button
		}
		else
		{
			ms_delay(100);							// Wait 300 ms
			GPION->DATA ^=(1<<1);				// LED D1 is toggling
		}
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