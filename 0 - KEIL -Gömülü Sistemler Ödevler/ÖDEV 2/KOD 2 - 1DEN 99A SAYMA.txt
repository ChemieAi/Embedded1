#include "TM4C123.h"                    // Device header

uint8_t const SEG_Tablo[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void ms_delay(int32_t ms);

int main()
{
    uint8_t tens, ones;
    SYSCTL->RCGC2 |= 0x00000002;        // Enable clock for PORTB
    GPIOB->DIR |= 0xFF;                 // Set all pins of PORTB as output
    GPIOB->DEN |= 0xFF;                 // Set all pins of PORTB as digital 

    // Initialize PORTA for common leg control
    SYSCTL->RCGC2 |= 0x00000001;        // Enable clock for PORTA
    GPIOA->DIR |= (1<<2);               // Set PA2 as output for left display's common leg
    GPIOA->DEN |= (1<<2);               // Set PA2 as digital pin for left display's common leg

    while(1)
    {
        for(tens = 0; tens < 10; tens++)
        {
            for(ones = 0; ones < 10; ones++)
            {
                for(int i = 0; i < 100; i++) // Multiplexing loop
                {
                    // Activate right display (ones digit)
                    GPIOA->DATA &= ~(1<<2);          // Turn off left display
                    GPIOB->DATA = (GPIOB->DATA & ~(0x7F)) | SEG_Tablo[ones]; // Set segments for ones
                    GPIOB->DATA |= (1<<7);           // Turn on right display
                    ms_delay(1);                     // Display on for 1 ms

                    // Activate left display (tens digit)
                    GPIOB->DATA &= ~(1<<7);          // Turn off right display
                    GPIOB->DATA = (GPIOB->DATA & ~(0x7F)) | SEG_Tablo[tens]; // Set segments for tens
                    GPIOA->DATA |= (1<<2);           // Turn on left display
                    ms_delay(1);                     // Display on for 1 ms
                }
                ms_delay(10); // Total delay to make up approximately 500ms cycle
            }
        }
    }
}

void ms_delay(int32_t ms)
{
    int i, j;
    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 3180; j++)
        {
            __NOP(); // This is a CPU No Operation command to waste some time
        }
    }
}
