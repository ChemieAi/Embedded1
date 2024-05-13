#include "TM4C123GH6PM.h"

int main(void)
{
   unsigned int state;
   SYSCTL->RCGCGPIO |= 0x20;   /* enable clock to GPIOF */
   GPIOF->LOCK = 0x4C4F434B;   // unlockGPIOCR register
   GPIOF->CR = 0x01;           // Enable GPIOPUR register enable to commit
   GPIOF->PUR |= 0x10;        // Enable Pull Up resistor PF4
   GPIOF->DIR |= 0x02;          //set PF1 as an output and PF4 as an input pin
   GPIOF->DEN |= 0x12;         // Enable PF1 and PF4 as a digital GPIO pins 

    while(1)
    {   
        state = GPIOF->DATA & 0x10;
        GPIOF->DATA = (~state>>3);    /* put it on red LED */
    }
}