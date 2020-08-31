/*********************************************
    *main.c

    *SER486 Assignment 3
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *This file runs the temp.c file that outputs
    *the value of the tempature sensor

 **********************************************/
#include <avr/io.h>
#include "uart.h"
#include "simpledelay.h"
#include "simpleled.h"
#include "temp.h"



int main(void)
{
    uart_init();
    temp_init();
    uart_writestr("SER 486 HW4 – Nathaniel Bryant\n\r");
    long int tempature;


    while(1)
    {
        temp_start();

        while(temp_is_data_read())
        {

        }
        tempature = temp_get();
        uart_writedec32(tempature);
        uart_writechar('\n');
        uart_writechar('\r');
        delay(100);


    }

    return 0;
}
