/*
Author: Nathaniel Bryant
ASURITE: nsbryan1
Class: SER 486
Description: Creates a blinking led
 */

#include <avr/io.h>

/*******************************

function: Creates a delay of the requested length

input:
delayTime: the value of the requested time

**********************************/

void delay(unsigned int delayTime)
{
    unsigned int ii = 0;

    while(ii < delayTime)
    {
        ii++;
    }
}



int main(void)
{
    unsigned int delayValue = 60000;
    //Sets PINB 1 and goes to
    DDRB |= (1<<1);
    while(1) {

        PORTB |= (1<<1);
        delay(delayValue);


        PORTB &= ~(1<<1);


        delay(delayValue);


    }

    return 0;
}
