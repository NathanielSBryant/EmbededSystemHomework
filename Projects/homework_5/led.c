/*********************************************
    *delay.c

    *SER486 Project 1
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Implents a flashing led functionality using a delay class
    * and a finite state machine

 **********************************************/

#include "led.h"
#include "delay.h"

volatile char * blink_msg;//Holds the msg
unsigned int blink_pos; //What postion we are in the message
unsigned char blink_state; //what is the state of the LED FSM



/**********************************
*
* void state_1()
*
*
* This code is just running state_1 of the
* FSM
*
* arguments:
*   None
*
* Changes:
*   May change the state of the FSM
*   To state_2
**********************************/
void state_1()
{
    unsigned int delay;

    //Sets the delay for each character
    switch(blink_msg[blink_pos])
    {

        //A blank space will not go to state 2
        case ' ' :
            delay = 1000;
            led_off();
            break;

        case '-' :
            blink_state = '2';
            delay = 750;
            led_on();
            break;

        case '.' :
            blink_state = '2';
            delay = 250;
            led_on();
            break;

        default :
            blink_state = '2';
            delay = 0;
            led_off();
            break;
    }
    delay_set(0 , delay);


}


/**********************************
*
* void state_2()
*
*
* This code is just running state_2 of the
* FSM
*
* arguments:
*   None
*
* Changes:
*   Changes the state of the FSM to 1
**********************************/
void state_2()
{
    delay_set(0,100);
    led_off();
    blink_state = '1';
}


/**********************************
*
* void led_set_blink(char * msg)
*
* This code sets saves the message to the class
* and resets the delay
*
* arguments:
*   msg:
*       A string with null termniation representing the msg
*
* Changes:
*   Resets the delay
**********************************/
void led_set_blink(char * msg)
{
    blink_msg = msg;
    blink_pos = 0;
    blink_state = '1';
    delay_set(0,0);//Rests the delay
    led_off();

}


/**********************************
*
* void led_update()
*
* This code will select the state that the FSM
* will run
*
*
* arguments:
*   None
*
* Changes:
*   None
**********************************/
void led_update()
{
    if(delay_isdone(0))
    {
        switch(blink_state)
        {
            case '1': //For state 1
                state_1();
            break;
            case '2': //For state 2
                state_2();
            break;

        }
        if (blink_msg[blink_pos+1] != 0)
        {
            blink_pos++;
        }
        else
        {
            blink_pos = 0;
        }

    }

}




