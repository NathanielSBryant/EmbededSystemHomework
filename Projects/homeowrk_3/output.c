/********************************************************
 * output.c
 *
 * SER486 Assignment 4
 * Spring 2018
 * Written By:  Doug Sandy (instructor)
 * Modified By: Nathaniel Bryant
 *
 * this file implements functions associated with SER486
 * homework assignment 4.  The procedures implemented
 * provide led and console output support for debugging
 * of future SER 486 assignments.
 *
 * functions are:
 *    writestr(char *)  - a function to write an ascii
 *                        null-terminated string to the
 *                        avr atmega 328P uart port.
 *                        (instructor provided)
 *
 *    writehex8(unsigned char) - a function to write the
 *                        hexadecimal representation of
 *                        an 8-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    writehex16(unsigned int) - a function to write the
 *                        hexadecimal representation of
 *                        a 16-bit unsigned integer to
 *                        avr atmega 328P uart port.
 *
 *    blink_led(char *) - a function to send a specific
 *                        blink pattern to the development
 *                        board's user-programmable LED.
 *
 *    delay(unsigned int) - delay code execution for
 *                        the specified amount of milliseconds.
 *                        (instructor provided)
 */

 #include "hw4lib.h"

 /* macro definitions used by delay() */
 #define MSEC_PER_SEC     1000
 #define CLOCKS_PER_LOOP  16
 #define LOOPS_PER_MSEC   ((F_CPU/MSEC_PER_SEC)/CLOCKS_PER_LOOP)

/**********************************
 * delay(unsigned int msec)
 *
 * This code delays execution for for
 * the specified amount of milliseconds.
 *
 * arguments:
 *   msec - the amount of milliseconds to delay
 *
 * returns:
 *   nothing
 *
 * changes:
 *   nothing
 *
 * NOTE: this is not ideal coding practice since the
 * amount of time spent in this delay may change with
 * future hardware changes.  Ideally a timer should be
 * used instead of a set of for loops.  Timers will be
 * taught later in the semester.
 */
void delay(unsigned int msec)
{
    volatile unsigned i,j ;  /* volatile prevents loops from being optimized away */

    /* outer loop, loops for specified number of milliseconds */
    for (i=0; i<msec; i++) {
        /* inner loop, loops for 1 millisecond delay */
        for (j=0;j<LOOPS_PER_MSEC;j++) {}
    }
}


/**********************************
 * writestr(char * str)
 *
 * This code writes a null-terminated string
 * to the UART.
 *
 * arguments:
 *   str - a pointer to the beginning of the
 *         string to be printed.
 *
 * returns:
 *   nothing
 *
 * changes:
 *   the state of the uart transmit buffer will
 *   be changed by this function.
 *
 * NOTE: uart_init() should be called this function
 *   is invoked for the first time or unpredictable
 *   UART behavior may result.
 */
void writestr(char * str)
{
    unsigned int i;

    /* loop for each character in the string */
    for (i=0; str[i]!=0;i++) {
        /* output the character to the UART */
        uart_writechar(str[i]);
    }
}

/************************************************************
* STUDENT CODE BELOW THIS POINT
*************************************************************/


/**********************************
* numtoHexAscii(int numValue)
*
* This code returns the ASCII value of the hex number
* given by an int value
*
* arguments:
*   numValue - the int value of a hex value
*
* returns: Ascii value of the given hex value
*
*
**********************************/

int numtoHexAscii (int numValue)
{
    //Checks if the value needs to be a letter or not

    if(numValue < 9)//If below 9 the ASCII of 0-9 is 48-58
    {
        numValue += 48;
    }
    else //If value is above 9 the ASCII of A-F is 65-70
    {
        numValue += 55;
    }

    return numValue;

}


/* Student-provided function comments go here */
/**********************************
* writehex8(unsigned char num)
*
* This code takes a 8bit char and sends it
* 4 bits at time to the uart writer by first
* seperating the bits and then converting them
* to ascii
*
* arguments:
*   num - a 8 bit char that holds two seperate hex values
*
*
*
**********************************/
void writehex8(unsigned char num)
{
    /* student-provided implementatino code goes here*/
    int andMask = 15;//and mask of 0x1111
    uart_writechar(numtoHexAscii((andMask&(num>>4))));

    uart_writechar(numtoHexAscii((andMask & num)));


}

/* Student-provided function comments go here */
/**********************************
* writehex16(unsigned int num)
* This code writes all a 16 bit int value as a ASCII
* hex value by seperating it to 8 bits and sending it to
* The writehex8() function
*
* arguments:
*   num - a 16 bit int value representing 4 seperate
*   hex values
*
*
*
**********************************/
void writehex16(unsigned int num)
{
    /* student-provided implementatino code goes here */
    int andMask = 255; //And mask of 0x11111111
    unsigned int value2 = (num & andMask);
    unsigned int value1 = ((num>>8) & andMask);
    writehex8(value1);
    writehex8(value2);

}

/* Student-provided function comments go here */
/**********************************
* blink_led(char *msg)
*
* This code creates a morse code signal by
* flashing the led of PORTB1
*
* arguments:
*   msg - a string termnated with a null termenator
*   holding a '-', '.' , or ' '
*
*
*
**********************************/
void blink_led(char *msg)
{
    /* student-provided implementatino code goes here */
    //Runs untill it finds the null termnation
    while(*(msg) != 0x00)
    {

        //Waits 250 MS
        if(*(msg) == '.')
        {
            PORTB |= (1<<1); //Turns on the LED
            delay(250);
            PORTB &= ~(1<<1); //Turns off the LED
            delay(100);
        }
        //Waits 750 ms
        else if(*(msg) == '-')
        {
            PORTB |=(1<<1);//Turns on the LED
            delay(750);
            PORTB &= ~(1<<1); //Turns off the LED
            delay(100);
        }
        //Waits 1000 ms
        else if(*(msg) == ' ')
        {
             delay(1000);
        }

        msg++;

    }
}
