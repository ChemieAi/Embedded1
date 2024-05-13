/* Embedded & Real-Time System Design, Expirement-1: Initialize GPIO Pins
November 2023
EK-TM4C123GXL LaunchPad Board Hardware Connection
PF4 GPIO SW1 
PF0 GPIO SW2 
PF1 GPIO RGB LED (Red) 
PF2 GPIO RGB LED (Blue) 
PF3 GPIO RGD LED (Green)

PC0-PC3 is used for JTAG connections to the debugger on the LaunchPad. 
So we�d better do not use these pins normally.
*/

#include "TM4C123.h"                    // Device header
uint8_t const SEG_Tablo[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 
0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void ms_delay(int32_t ms);
	
int main()
{
	uint8_t say=0;
	SYSCTL->RCGC2 |= 0x00000022;		//enabling clock for PORTF, PORTa
	GPIOF->DIR |=0X02;			// Set PIN 1 output
	GPIOF->DEN |=0X02;			// Set PIN 1 digital 
	GPIOB->DIR |=0XFF;			// Set PIN 1 output
	GPIOB->DEN |=0XFF;			// Set PIN 1 digital 
	
	while(1)
	{
		for(say=0;say<10;say++)
    {
		GPIOB->DATA =SEG_Tablo[say];		// say
		ms_delay(500);				// Wait 300 ms

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