/* Generates 10KHz and 50% duty cycle on PF2 pin of TM4C123 Tiva C Launchpad */
/* PWM1 module and PWM generator 3 of PWM1 module is used */
#include "TM4C123GH6PM.h"
void Delay_ms(int n);
int main(void)
{
/* Clock setting for PWM and GPIO PORT */
SYSCTL->RCGCPWM |= 2;       /* Enable clock to PWM1 module */
SYSCTL->RCGCGPIO |= 0x20;   /* Enable system clock to PORTF */
SYSCTL->RCC &= ~0x00100000; /* Directly feed clock to PWM1 module without pre-divider */

/* Setting of PF2 pin for M1PWM6 channel output pin */
GPIOF->AFSEL |= (1<<2);     /* PF2 sets a alternate function */
GPIOF->PCTL &= ~0x00000F00; /*set PF2 as output pin */
GPIOF->PCTL |= 0x00000500; /* make PF2 PWM output pin */
GPIOF->DEN |= (1<<2);      /* set PF2 as a digital pin */

/* PWM1 channel 6 setting */
PWM1->_3_CTL &= ~(1<<0);   /* Disable Generator 3 counter */
PWM1->_3_CTL &= ~(1<<1);   /* select down count mode of counter 3*/
PWM1->_3_GENA = 0x0000008C; /* Set PWM output when counter reloaded and clear when matches PWMCMPA */
PWM1->_3_LOAD = 16000;   /* set load value for 1kHz (16MHz/16000) */
PWM1->_3_CMPA = 8000-1;  /* set duty cyle to 50% by loading of 16000 to PWM1CMPA */
PWM1->_3_CTL = 1;         /* Enable Generator 3 counter */
PWM1->ENABLE = 0x40;      /* Enable PWM1 channel 6 output */ 
    while(1)
    {
			//do nothing 
    }
}
/* This function generates delay in ms */
/* calculations are based on 16MHz system clock frequency */
void Delay_ms(int time_ms)
{
    int i, j;
    for(i = 0 ; i < time_ms; i++)
        for(j = 0; j < 3180; j++)
            {}  /* excute NOP for 1ms */
}

