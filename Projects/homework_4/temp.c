/*********************************************
    *main.c

    *SER486 Assignment 3
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implements the ability to use the tempature sensor
    *for the ATMEGA

 **********************************************/


#include "temp.h"

#define ADCMUX  (* ((volatile char*) 0x7C))
#define ADCSRA (* ((volatile char *) 0x7A))
#define ADCL (* ((volatile char *) 0x78))
#define ADCH (* ((volatile char *) 0x79))



#define ADSC 6
#define ADEN 7
#define ADPS 0
#define REFS 6
#define MUX 0

/**********************************
* temp_init()
*
* This code sets up the ADC and for the tempature sensor
*
* arguments:
*   none
*
* changes:
*   Changes the ADCMUX::MUX to 1000 for tempature sensor
*   Changes the ADCMUC::REFS to 11 for 1.1 comparision volatage
*   Changes the ADCSRA::ADEN to 1
*   Changes the ADCSRA::ADPS to 110
*
**********************************/
void temp_init()
{

    ADCSRA |= (1<<ADEN);//Turns on the ADC
    ADCSRA |= (6<<ADPS);//Sets the prescalar to 64
    ADCMUX  |= (8<<MUX); //Sets the mux pin for tempature sensor
    ADCMUX  |= (3<<REFS);// Sets volatge comparision to 1.1v

}


/**********************************
* temp_is_data_read()
*
* This code will return when the tempature sensor has done reading
* 1 while still reading and 0 when done reading
*
* arguments:
*   none
*
* returns:
*   An int value of 1 meaning reading is still going 0 meaning read is done
**********************************/
int temp_is_data_read()
{
    return ((ADCSRA>>ADSC)& 1);

}



/**********************************
* temp_start())
* This code starting the ADC reading process
*
*
* arguments:
*   none
*
* returns:
*   none
*
* changes:
*   Changes the ADSC bit to 1 causing the
**********************************/
void temp_start()
{
    ADCSRA |= (1<<ADSC);
}

/**********************************
* temp_start())
* This code starting the ADC reading process
*
*
* arguments:
*   none
*
* returns:
*   A long int value
*
**********************************/
int temp_get()
{
    long int reading = ADCL;

    reading |= (ADCH<<8);

    return ((reading*101)/101)-273;

}
