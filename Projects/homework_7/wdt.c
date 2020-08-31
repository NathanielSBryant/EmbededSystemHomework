/*********************************************
    *wtc.c

    *SER486 Project 3
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Watchdog timer class that should stop hard resets

 **********************************************/
#include "wdt.h"
#include "alarm.h"
#include "log.h"
#include "config.h"
#define WDTCSR (* ((volatile char*) 0x60))
#define WDIE (6)
#define WDE (3)


#pragma GCC push_options
#pragma GCC optimize ("Os")

//Inits the Watchdog class for 2 seconds and allows interups
void wdt_init()
{
    WDTCSR |= (7<<0);//Sets clock prescaller to 2 seconds
    WDTCSR |= (1<<WDE);//Starts the Watch dog timer on intrupt

}
#pragma GCC pop_options

//Rests watchdog timer
void wdt_reset()
{
    __BUILTIN_AVR_WDR;
}


//Restard the entire system
void wdt_force_restart()
{
    log_add_record(0x01);
    log_update_noisr();
    config_update_noisr();
    WDTCSR &= ~(1<<WDE);
    WDTCSR |= (1<< WDIE);//Sets the WDT to reset after next time
    while(1);
}

//The interupt for hte watchdog timer if called twice will shutdown the system
void __vector_6(void) __attribute__ ((signal,used, externally_visible));
void __vector_6(void)
{
    log_add_record(0x02);
    WDTCSR &= ~(1<<WDE);
    WDTCSR |= (1<< WDIE);//Sets the WDT to reset after next time

}
