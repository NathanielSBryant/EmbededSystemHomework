/*********************************************
    *delay.c

    *SER486 Project 1
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implements a counter system using an interupt function

 **********************************************/


#define TCCR0A (* ((volatile char*) 0x44))
#define TCCR0B (* ((volatile char*) 0x45))
#define TIMSK0 (* ((volatile char*) 0x6E))
#define OCR0A  (* ((volatile char*) 0x44))
#define SREG   (* ((volatile char*) 0x5F))

volatile unsigned int count[2];
unsigned int  limit[2];
static unsigned char initialized;
/**********************************
*
* void init()
*
*
* This code initalizes the timer and interupt
* will only be called once in set()
*
* arguments:
*   None
*
* Changes:
*   Turns on CTC mode and OCR0A compare match
*   Sets prescaler to 64 with a compare of 249
*   Initilaizes the count and limit arrays
*   creates a static variable initialized
**********************************/
void delay_init()
{
    TCCR0A |= ((1<<7) | (1<<6)); //Sets the OCR0A on compare match
    TCCR0A |= ((1<<1)); //Sets to CTC mode


    //Sets interrupt rate to 1 milli second
    TCCR0B |= ((1<<1) | (1<<0));//Sets prescaller to 64
    OCR0A |= 249; //Sets compare rate to 249


    TIMSK0 |= (1<<1); //Sets the interrupt for OCR0A



    initialized = 1;
    limit[0] = 0;
    limit[1] = 0;
    count[0] = 0;
    count[1] = 1;

}


/**********************************
*
* unsigned int get(unsigned int num)
*
* This code returns the current value of the timer
* of the specifed timer
*
* returns:
*   the value of the timer since start
*
* arguments:
*   num : what selected timer is desiered
*
* Changes:
*   None
**********************************/
unsigned int delay_get(unsigned int num)
{
    unsigned int bitState = SREG;
    __builtin_avr_cli(); //Turn off interrupts
    //Atomic interaction is active
     unsigned int countValue = count[num];
     SREG = bitState;
     //Atomic off
     return countValue;
}

/**********************************
*
* void set(unsigned int num , unsigned int time)
*
* Sets the state of a timer and the length of
* that timer
*
*
* arguments:
*   num : what selected timer is desiered to set
*   msec: the time limit in milli seconds
*
* Changes:
*   None
**********************************/
void delay_set(unsigned int num, unsigned int msec)
{

    if(initialized == 0)
    {
        delay_init();
    }

    unsigned int bitState = 0 | SREG; //Save SREG state
    __builtin_avr_cli(); //Turn off interrupts
    //We are now atomic at this point
    limit[num] = msec;
    count[num] = 0;
    SREG = bitState;
    //Atomic is no longer active
}

/**********************************
*
* unsigned int isdone(unsigned int num)
*
* Returns the state of the timer if its done or not
*
*  Returns:
*   an unsigned int value 0 being not done and 1 being done
*
* arguments:
*   num : what selected timer is desiered to check
*
*
* Changes:
*   None
**********************************/
unsigned int delay_isdone(unsigned int num)
{
    unsigned int result = 0;

    if(count[num] == limit[num])
    {
        result = 1;
    }
    return result;

}


/**********************************
*
* void __vector_14(void)
*
* An interrupt that adds 1 to the count as long as count < limit
*
*  Returns:
*   nonne
*
* arguments:void __vector_14(void)void __vector_14(void)
*   none
*
*
* Changes:
*   None
**********************************/
void __vector_14(void) __attribute__ ((signal,used, externally_visible));
void __vector_14(void)
{
    if(!delay_isdone(0))
    {
        count[0] += 1;
    }
    if(!delay_isdone(1))
    {
        count[1] +=1;
    }

}



