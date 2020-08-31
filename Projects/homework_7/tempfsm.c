/*********************************************
    *tempfsm.c

    *SER486 Project 3
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *Just a finite state machine with temp values

 **********************************************/
#include "log.h"
#include "alarm.h"
#include "led.h"

#define NORM1 (0)
#define NORM2 (1)
#define NORM3 (2)
#define WARN_LO_1 (3)
#define WARN_LO_2 (4)
#define WARN_HI_1 (5)
#define WARN_HI_2 (6)
#define CRITICAL_HI (7)
#define CRITICAL_LO (8)

unsigned char state;//state of the FSM


/**********************************
*
* void tempfsm_init()
*
*
    Inits the alarm class for the changes not much else is needed

*
* Changes:
*
**********************************/
void tempfsm_init()
{
    alarm_init();
}
/**********************************
*
* void state_hi_crit(int current , int hicrit)
*
*
    This is the HI crit state that must be run

    ARGUMENT: current= CURRENT TEMP
        HI CRIT= the high temp
*
* Changes:
*
**********************************/

void state_hi_crit(int current , int hicrit)
{
    if(current < hicrit)
    {
        state= WARN_HI_2;
        alarm_send(EVENT_HI_ALARM);
        log_add_record(EVENT_HI_ALARM);
        led_set_blink("-");
    }
    else
    {
        alarm_send(EVENT_HI_WARN);
        log_add_record(EVENT_HI_WARN);
    }
}

/**********************************
*
* void state_hi_warn(int current , int hicrit)
*
*
    This is the HI warn state that must be run

    ARGUMENT: current= CURRENT TEMP
        HI CRIT= the high temp
        HI warn= the high warning temp
*
* Changes:
*
**********************************/
void state_hi_warn(int current , int hiwarn , int hicrit)
{
    if(current >= hicrit)
    {
        state = CRITICAL_HI;
        alarm_send(EVENT_HI_ALARM);
        log_add_record(EVENT_HI_ALARM);
        led_set_blink(".");
    }
    else if(current < hiwarn)
    {
        state= NORM3;
        led_set_blink(" ");
    }
    else
    {
        alarm_send(EVENT_HI_WARN);
        log_add_record(EVENT_HI_WARN);
    }

}

/**********************************
*
* void state_norm(int current , int hicrit)
*
*
   Normal state

    ARGUMENT: current= CURRENT TEMP
        lo CRIT= the lo temp
        HI warn= the high warning temp
*
* Changes:
*
**********************************/
void state_norm(int current , int hiwarn , int lowarn)
{

    if(current >= hiwarn)
    {
        state = WARN_HI_1; //Change State
        alarm_send(EVENT_HI_WARN);
        log_add_record(EVENT_HI_WARN);
        led_set_blink("-");

    }
    else if(current <= lowarn)
    {
        state = WARN_LO_1; //Change state
        alarm_send(EVENT_LO_WARN);
        log_add_record(EVENT_LO_WARN);
        led_set_blink("-");
    }
    else
    {
        led_set_blink(" ");
    }

}

/**********************************
*
* void state_lo_crit(int current , int hicrit)
*
*
   Normal state

    ARGUMENT: current= CURRENT TEMP
        lo CRIT= the lo temp
        lo warn= the lo warning temp
*
* Changes:
*
**********************************/
void state_lo_crit(int current , int locrit)
{
    if(current > locrit)
    {
        state= WARN_LO_2;
        alarm_send(EVENT_LO_WARN);
        log_add_record(EVENT_LO_WARN);
        led_set_blink("-");
    }
    else
    {
        alarm_send(EVENT_LO_ALARM);
        log_add_record(EVENT_LO_ALARM);
    }

}
/**********************************
*
* void state_lo_crit(int current , int hicrit)
*
*
   Normal state

    ARGUMENT: current= CURRENT TEMP
        lo CRIT= the lo temp
        lo warn= the lo warning temp
*
* Changes:
*
**********************************/
void state_lo_warn(int current , int lowarn , int locrit)
{
    if(current <= locrit)
    {
        state = CRITICAL_LO;
        alarm_send(EVENT_LO_ALARM);
        log_add_record(EVENT_LO_ALARM);
        led_set_blink(".");
    }
    else if(current >= lowarn)
    {
        state = NORM2;
        led_set_blink(" ");
    }
    else
    {
        alarm_send(EVENT_LO_WARN);
    }

}

/**********************************
*
* tempfsm_update(int current, int hicrit, int hiwarn, int locrit, int lowarn)
*
*
   Updates the FSM machine

    ARGUMENT: current= CURRENT TEMP
        lo CRIT= the lo temp
        lo warn= the lo warning temp
*
* Changes:
*
**********************************/
void tempfsm_update(int current, int hicrit, int hiwarn, int locrit, int lowarn)
{
    switch(state)
    {
        case NORM2:{
            state_norm(current , hiwarn , lowarn);
            break;
        }
        case NORM3:{
            state_norm(current , hiwarn , lowarn);
            break;
        }
        case NORM1:
        {
            state_norm(current , hiwarn , lowarn);
            break;
        }
        case WARN_LO_1:
        {
            state_lo_warn(current , lowarn , locrit);
            break;
        }
        case WARN_LO_2:
        {
            state_lo_warn(current , lowarn , locrit);
            break;
        }
        case CRITICAL_LO:
        {
            state_lo_crit(current ,  locrit);
            break;
        }
        case WARN_HI_1:
        {
            state_hi_warn(current , hiwarn , hicrit);
            break;
        }
        case WARN_HI_2:
        {
            state_hi_warn(current , hiwarn , hicrit);
            break;
        }
        case CRITICAL_HI:
        {
            state_hi_crit(current , hicrit);
            break;
        }

    }


}

/**********************************
*
* tempfsm_reset()
*
*
   resets the FSM


*
* Changes:
*
**********************************/
void tempfsm_reset()
{
    state = NORM1;
}
