/*********************************************
    *main.c

    *SER486 Assignment 3
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *This file runs the code of the output file by writing an
    *8 bit hex value of 0x0A and a 16 bit hex value 0xC0DE
    *and sends the string literal "SER-486 HW3 Nathaniel Bryant\n\r"

 **********************************************/


#include <avr/io.h>
#include "output.c"
#include "hw4lib.h"

int main(void)
{
    // Insert code
    uart_init();
    DDRB |= (1<<1);
    writestr("SER-486 HW3 Nathaniel Bryant\n\r");
    writehex8(0x0A);
    writestr("\n\r");//Creates a new line and a carriage return
    writehex16(0xC0DE);
    writestr("\n\r");//Creates a new line and a carriage return


    while(1)
    {
        blink_led("--- -.-");
        }


    return 0;
}
