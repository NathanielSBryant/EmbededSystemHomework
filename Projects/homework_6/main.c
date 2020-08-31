/*********************************************
    *main.c

    *SER486 Project 2
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implments the eeprom, vpd, and config classes

 **********************************************/

#include <avr/io.h>
#include "util.h"
#include "uart.h"
#include "config.h"
#include "led.h"
#include "log.h"
#include "rtc.h"
#include "vpd.h"
#include "eeprom.h"
int main(void)
{

    // Insert code
    uart_init();
    config_init();
    led_init();
    log_init();
    rtc_init();
    vpd_init();

    unsigned char dumped = 0;

    led_set_blink("--- -.-");
    rtc_set_by_datestr("01/01/2019 00:00:00");

    uart_writestr("SER 486 Project 2 - Nathaniel Bryant \n\r");
    uart_writestr(vpd.model);
    uart_writestr("\n\r");
    uart_writestr(vpd.manufacturer);
    uart_writestr("\n\r");
    uart_writestr(vpd.token);
    uart_writestr("\n\r");
    config.use_static_ip = 1;
    config_set_modified();
    log_clear();
    log_add_record(0xaa);
    log_add_record(0xbb);
    log_add_record(0xcc);
    log_update();




    while(1)
    {

        led_update();
        log_update();
        config_update();

        if(!eeprom_isbusy() && !dumped)
        {
             dump_eeprom(0,0x100);
             dumped = 1;

        }


    }


    return 0;
}
