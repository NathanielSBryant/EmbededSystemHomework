/*********************************************
    *main.c

    *SER486 Project 1
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implements the blinking led with led.c and delay.c
    *Also implemnts the real time clock with timer1.c and rtc.c

 **********************************************/

#include <avr/io.h>
#include "led.h"
#include "delay.h"
#include "timer1.h"
#include "rtc.h"
#include "uart.h"

int main(void)

    //Inits uart led and rtc
    uart_init();
    led_init();
    rtc_init();


    //Code given by Profesor Sandy
    /* get baseline performance */
    signed long c1=0;
    delay_set(1,10000);
    while(!delay_isdone(1)) {c1++; }

    /* measure performance with led_update */
    signed long c2 = 0;
    delay_set(1, 10000);
    while(!delay_isdone(1)) {
        led_update();
        c2++;
    }

    /* display the results */
    uart_writedec32(c1);
    uart_writestr(" ");
    uart_writedec32(c2);
    uart_writestr("\r\n");


    //Boiler plate opening
    uart_writestr("SER 486 Project 1 - Nathaniel Bryant \n\r");

    //Sets the time of the STC
    rtc_set_by_datestr("01/01/2019 00:00:00");
    //"OK" in morse code
    led_set_blink("--- -.-");

    while(1)
    {
        led_update();
        delay_set(1 , 500);
        while(!delay_isdone(1));
        uart_writestr(rtc_get_date_string());
        uart_writestr("\r");//This goes back to the same line we were writing to

    }





    return 0;
}
