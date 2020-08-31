/*********************************************
    *timer1.c

    *SER486 Project 1
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implments a 1hz(1 second) 16 bit timer

 **********************************************/
#define TCCR1A (* ((volatile char*) 0x80)) //Defines the register for TCCR1A
#define TCCR1B (* ((volatile char*) 0x81)) //Defines the register for TCCR1B
#define TCCR1C (* ((volatile char*) 0x82)) //Defines the register for TCCR1C
#define TIMSK1 (* ((volatile char*) 0x6F)) //Defines the register for the TIMSK1
#define OCR1A  (((* ((volatile char*) 0x89))<<8) | ((* ((volatile char*) 0x88)))) //WIll be the compare value used for bug testing
#define OCR1AH (* ((volatile char*) 0x89)) //The high value of the compare value 8 bits
#define OCR1AL (* ((volatile char*) 0x88)) //The low value of the compare value 8 bits
#define SREG   (* ((volatile char*) 0x5F)) //The interupt state of the program registers
volatile unsigned long timer_count; //The counter for each second

/**********************************
*
* void timer1_init()
*
* Inits the timer for use
*
* arguments:
*   None
*
* Changes:
*   Sets the TCCR1A to OCR1A compare
*   Sets the TCCR1A/B to CTC mode comparing OCR1A
*   Turns on the compare match interupt using TIMSK1
*   Sets the compare match to 15624
*   Sets clock prescaper to 1024
**********************************/
void timer1_init()
{
    TCCR1A |= ((1<<7)|(1<<6)); //setting COM1A0 to 1 for compare match
    TCCR1B |= (1<<3); //Turning on CTC mode comparing to OCR1A
    TCCR1B |= ((1<<2) | (1<<0));//Turns on prescaller to 1024
    TIMSK1 |= (1<<1);//Turns on compare ORC1A active
    //Sets the OCR1A to 15524
    OCR1AH |= 0x3D; //Sets limit to 15624 needs to be in two parts
    OCR1AL |= 0x08;


}

/**********************************
*
* void timer1_get()
*
* Returns the value of the timer with an atomic function
*
* arguments:
*   None
*
* Changes:
*   None
**********************************/
unsigned long timer1_get()
{
    unsigned int bitState = SREG;
    __builtin_avr_cli(); //Turn off interrupts
    //WE ARE NOW ATOMIC
    unsigned long countValue = timer_count;
    SREG = bitState;
    //We are not longer atomic
    return countValue;

}

/**********************************
*
* void timer1_clear()
*
* Clears the counter with an atomic function
*
* arguments:
*   None
*
* Changes:
*   None
**********************************/
void timer1_clear()
{
    unsigned int bitState = SREG;
    __builtin_avr_cli(); //Turn off interrupts
    //WE ARE NOW ATOMIC
    timer_count = 0;
    SREG = bitState;
    //WE are not longer atomic

}

/**********************************
*
* __vector_11()
*
* Interupt 12 on table that adds 1 to timer_count
* Triggers only when timer has reached OCR1A compare value
*
* arguments:
*   None
*
* Changes:
*   None
**********************************/
void __vector_11(void) __attribute__ ((signal,used, externally_visible));
void __vector_11(void)
{
    timer_count++;

}
