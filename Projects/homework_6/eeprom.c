/*********************************************
    *eeprom.c

    *SER486 Project 2
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implements the eeprom system with an interupt
    *will only write or read not both

 **********************************************/

#include "eeprom.h"
#define EEAR (* ((volatile char*) 0x41))
#define SREG   (* ((volatile char*) 0x5F))
#define EEDR (* ((volatile char*) 0x40))
#define EECR (* ((volatile char*) 0x3F))
#define EERIE (3)
#define EERE (0)
#define EEPE (1)
#define EEMPE (2)


unsigned char writebuff[64]; // The write buffer for eeprom
unsigned char bufidx;//Buffer index
unsigned char writesize;//Size of the write in bytes
unsigned int writeaddr; //Address in eeprom to write to
unsigned volatile char write_busy; //State of the eeprom


/**********************************
*
* void eeprom_writebuf()
*
*
* Begins the write process by saving the size address and message to be written
*
* arguments:
*   unsigned char dsize: The size in bytes that is to be written
*   unsigned int addre: Address of the eeprom in memory
*   unsigned char * buff: Pointer to the information need to be read
*
* Changes:
*   Setts the interupts for the eeprom write
**********************************/
void eeprom_writebuf(unsigned int addr , unsigned char * buf , unsigned char dsize)
{
    //Waits for the eemprom not to be busy
    while(eeprom_isbusy());

    writeaddr = addr;
    write_busy = 1;
    bufidx = 0;
    //Saves the information into a seperate buffer
    int ii;
    for(ii = 0 ; ii < dsize ; ii++)
    {
        writebuff[ii] = buf[ii];
    }
    writesize = dsize;

    //Turns on the interupts for the EEPROM
    EECR |= (1<<EERIE);



}

/**********************************
*
* void eeprom_readbuf()
*
*
* Reads the eemprom information by putting it in a char pointer
*
* arguments:
*   unsigned char dsize: The size in bytes that is to be read
*   unsigned int addre: Address of the eeprom in memory
*   unsigned char * buff: Pointer to the location of the information to be written
*
* Changes:
*   none
**********************************/
void eeprom_readbuf(unsigned int addr , unsigned char * buf , unsigned char dsize)
{
    while(eeprom_isbusy());

    int ii;
    for(ii = 0 ; ii < dsize ; ii++)
    {

        EEAR = addr;//Sets the address to read
        EECR |= (1<<EERE); //Tells the EEPROM to read
        buf[ii] = EEDR; //Takes the data and saves it
        addr++;//Increase the address for the next read
    }


}

/**********************************
*
* int  eeprom_isbusy()
*
*
* Tells the state of the eeprom if work ca nbe done
*
* arguments:

*
* Returns:
*   The state of the eeprom 1 if busy 0 if not
**********************************/
int eeprom_isbusy()
{
    return(write_busy == 1);
}


/*
    NOTE THE CREDIT FOR THE COMPLIER CODE IS NOT ORIGIAL
    WAS GIVEN BY PROFESSOR SANDY IN LECTURE NOTES
*/
#pragma GCC push_options
#pragma GCC optimize ("Os")

/**********************************
*
* void __vector_22()
*
*
* Writes the data in the eeprom
*
* arguments:
*   none
* Changes:
*   Will be in a write state until writing is done
*   all changes will be reverted after write state is done
**********************************/
void __vector_22(void) __attribute__ ((signal,used, externally_visible));
void __vector_22(void)
{
    unsigned int bitState = SREG;
    __builtin_avr_cli(); //Turn off interrupts
    if(bufidx<writesize)
    {
        while(EECR & (1<<EEPE));
        EEAR = writeaddr;
        EEDR = writebuff[bufidx];
        EECR |= (1<<EEMPE);
        EECR |= (1<<EEPE);
        writeaddr++;
        bufidx++;
        SREG = bitState;
    }
    else
    {
        EECR &= ~(1<<EERIE);
        write_busy = 0;
    }


}
#pragma GCC pop_options
