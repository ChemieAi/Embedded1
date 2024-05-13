/* Embedded & Real-Time System Design, Expirement-1: Initialize GPIO Pins
November 2023
EK-TM4C123GXL LaunchPad Board Hardware Connection
PF4 GPIO SW1 
PF0 GPIO SW2 
PF1 GPIO RGB LED (Red) 
PF2 GPIO RGB LED (Blue) 
PF3 GPIO RGD LED (Green)

PC0-PC3 is used for JTAG connections to the debugger on the LaunchPad. 
So we’d better do not use these pins normally.
*/

#include "TM4C123.h"                    // Device header

void ms_delay(int32_t ms);
	
int main()
{
	SYSCTL->RCGC2 |= 0x00000020;		//enabling clock for PORTF
	GPIOF->DIR |=0X02;			// Set PIN 1 output
	GPIOF->DEN |=0X02;			// Set PIN 1 digital 
	while(1)
	{
		GPIOF->DATA |=0X02;		// LED Red is on
		ms_delay(300);				// Wait 300 ms
		GPIOF->DATA &=~0X02;	// LED Red & LED Green are of
		ms_delay(300);				// Wait 300 ms
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