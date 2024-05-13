#include "TM4C123.h"
#include <stdlib.h>
#include <stdint.h> 

void printString(char *s); 
void uartTransmit(char c); 
char uartReceive(void);
void delay(void);
void PLL_Init(void);

int main()
{		PLL_Init();
		SYSCTL->RCGCUART |= 0x1; // Enable the UART0 Module
    SYSCTL->RCGCGPIO |= 0x1; // Enable the clock to Port A since UART0 uses PA0 for RX and PA1 for TX
    GPIOA->DEN |= 0x3; // Enable digital functions for PA0 and PA1
    GPIOA->AFSEL |= 0x3; // Enable alternate function for PA0 and PA1
    GPIOA->PCTL |= 0x11; // Assign UART signals to PA0 and PA1
    UART0->CTL = 0x0; // Disable the UART
    UART0->IBRD = 43; // Baud Rate =  ( f / 16 x baud divisor
											// 115200=(80 000 000/(16 x divisor) integer portion for 9600 baud rate
    UART0->FBRD = 31; //11 Write the fractional portion for 9600 baud rate
    UART0->LCRH = 0x60; // Configure UART for data length of 8 bits, no parity bit, one stop bit, FIFOs disabled, no interrupts
    UART0->CC = 0x0; // Select the UART Baud Clock Source as system clock
    UART0->CTL = 0x301; // Enable the UART, RX and TX sections 
	
		SYSCTL->RCGCGPIO |= 0x20; // Enable the clock to the PORTF since LEDs are connected to PF1, PF2 and PF3
    GPIOF->DIR |= 0xE; // Configure LED pins to be an output
    GPIOF->DEN |= 0xE; // Enable digital functions for LED pins 
		GPIOF->DATA &= 0xF1; // Turn off the LEDs

		while(1) {
        printString("Do you want to blink the LEDs? [Y/N/R/G/B] "); 
        char answer = uartReceive(); 

        switch(answer) {
            case 'Y': 
                while(1)
                {
                    GPIOF->DATA = 0x2; // turn on the red LED 
                    delay();
                    if ((UART0->FR & (1<<4)) == 0) { // Check if new data is available
                        char newAnswer = UART0->DR; // Read the new data
                        if (newAnswer != 'Y') {
                            answer = newAnswer; // Update the answer to handle in the outer switch
                            break; // Exit the inner while loop
                        }
                    }
                    GPIOF->DATA = 0x4; // turn on the blue LED 
                    delay();
                    if ((UART0->FR & (1<<4)) == 0) { 
                        char newAnswer = UART0->DR; 
                        if (newAnswer != 'Y') {
                            answer = newAnswer; 
                            break; 
                        }
                    }
                    GPIOF->DATA = 0x8; // turn on the green LED 
                    delay();
                    if ((UART0->FR & (1<<4)) == 0) { 
                        char newAnswer = UART0->DR; 
                        if (newAnswer != 'Y') {
                            answer = newAnswer; 
                            break; 
                        }
                    } 
									
                }
						case 'N':
                GPIOF->DATA = 0x0; // turn off all LEDs
                break;
            case 'R':
                GPIOF->DATA = 0x2; // turn on the red LED only
                break;
            case 'G':
                GPIOF->DATA = 0x8; // turn on the green LED only
                break;
            case 'B':
                GPIOF->DATA = 0x4; // turn on the blue LED only
                break;
            default: 
                printString("You typed an invalid character"); 
                break;
        }
    }
}	
void printString(char *s)
{
	while(*s != NULL) 
	{
		uartTransmit(*(s++));
	}
}	
void uartTransmit(char c) 
{
	while(UART0->FR & (1<<5)); // if TX holding register is full, wait until it becomes empty 
	UART0->DR = c; 
}
char uartReceive()
{
	while(UART0->FR & (1<<4)); // if RX holding register is empty, wait until it becomes full  
	char data = UART0->DR; 
	return data;
}
void delay()
{
	int i; 
	for(i=0; i<1000000; i++); 
} 
void PLL_Init(void)
{
	// 0) Use RCC2
  SYSCTL->RCC2 |=  0x80000000;  // USERCC2
  // 1) bypass PLL while initializing
  SYSCTL->RCC2 |=  0x00000800;  // BYPASS2, PLL bypass
  // 2) select the crystal value and oscillator source
  SYSCTL->RCC = (SYSCTL->RCC &~0x000007C0)   // clear XTAL field, bits 10-6
                 + 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL->RCC2 &= ~0x00000070;  // configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL->RCC2 &= ~0x00002000;
  // 4) set the desired system divider
  SYSCTL->RCC2 |= 0x40000000;   // use 400 MHz PLL
  SYSCTL->RCC2 = (SYSCTL->RCC2 &~ 0x1FC00000)  // clear system clock divider
                  + (4<<22);      // configure for 80 MHz clock
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL->RIS &0x00000040)==0){};  // wait for PLLRIS bit
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL->RCC2 &= ~0x00000800;
}