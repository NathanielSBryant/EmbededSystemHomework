/*********************************************
    *util.c

    *SER486 Project 3
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *UTIL class for changing temps

 **********************************************/


#include "config.h"



/* update the configuration tcrit_hi limit with the specified value
* This function is called by the packet command parser.
*/
int update_tcrit_hi(int value)
{
    int testvalue = config.hi_warn;
    if(config.hi_warn < value && value < 0x3FF)
    {
        config.hi_alarm = value;
        config_set_modified();
        config_update();
        return 0;
    }
    return 1;

}

/* Update the configuration twarn_hi limit with the specified value
* This function is called by the packet command parser.
*/
int update_twarn_hi(int value)
{
        if(config.lo_warn < value && value < config.hi_alarm)
    {
        config.hi_warn = value;
        config_set_modified();
        config_update();

        return 0;
    }
    return 1;

}

/* Update the configuration tcrit_lo limit with the specified value
* This function is called by the packet command parser.
*/
int update_tcrit_lo(int value)
{
    if(config.lo_warn > value)
    {
        config.lo_alarm = value;
        config_set_modified();
        config_update();
        return 0;
    }
    return 1;

}



int update_twarn_lo(int value)
{

    if(config.lo_alarm < value && value < config.hi_warn)
    {
        config.lo_warn = value;
        config_set_modified();
        config_update();
        return 0;
    }
    return 1;

}
