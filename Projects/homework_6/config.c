/*********************************************
    *config.c

    *SER486 Project 2
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *eeprom information for the config

 **********************************************/

#include "eeprom.h"
#include "config.h"
#include "util.h"

struct config_struct config_defaults = {
    .token = "ASU",
    .hi_alarm = 0x3FF,
    .hi_warn = 0x3FE,
    .lo_alarm = 0x0001,
    .lo_warn = 0x0000,
    .use_static_ip = 0,
    .static_ip = {192,168,1,100},
    .checksum = 0
};
unsigned char config_modified;


/**********************************
*
* void config_init()
*
*
* inits the config struct from the eeprom and
* sets defaults if eeprom is incorrect
*
* arguments:
*
* Returns:
*
*
**********************************/
void config_init()
{
    //So what I'm doing here is crazy I'll explain
    //How the strucut is structured there is no blank room
    //I can just feed it the raw eeprom data and make it happy
    while(eeprom_isbusy()){};
    unsigned char * config_read;
    config_read = (unsigned char *) &config;
    eeprom_readbuf(0x040 , config_read , sizeof(config));
    if(!config_is_data_valid())
    {
        config_write_defaults();
        config_read = (unsigned char *) &config;
        eeprom_readbuf(0x040 , config_read , sizeof(config));
        config_modified = 0;
    }
}

/**********************************
*
* void config_update()
*
* updates the config struct in eeprom if its been modifed
*
* arguments:
*
* Returns:
*
*
**********************************/
void config_update()
{
    if(config_modified == 1 && !eeprom_isbusy())
    {
        update_checksum((unsigned char *) &config , sizeof(config));
        unsigned char * config_write;
        config_write = (unsigned char *) &config;
        eeprom_writebuf(0x040 , config_write , sizeof(config));
        config_modified = 0;
    }


}

/**********************************
*
* void config_update()
*
* Sets the modifed state
*
* arguments:
*
* Returns:
*
* Changes:
*   Changes the state to be in a modifed state
**********************************/
void config_set_modified()
{
    config_modified = 1;
}

/**********************************
*
*int config_is_data_valid()
*
* Checks the data is correct by checking the
* config token and the checksum
*
* arguments:
*
* Returns:
*   1 if data is correct 0 if correct
* Changes:
*
**********************************/
int config_is_data_valid()
{
    char * test = "ASU";
    char * compare = config.token;
    while((*test) != '\0')
    {
        if((*test) != (*compare))
        {
            return 0;
        }
    }

    return is_checksum_valid((unsigned char *) &config , sizeof(config));
}


/**********************************
*
*int config_is_data_valid()
*
* Writes the config default eeprom
*
* arguments:
*
* Returns:
*
* Changes:
*
**********************************/
void config_write_defaults()
{
    update_checksum((unsigned char *) &config_defaults , sizeof(config_defaults));
    unsigned char * config_write;
    config_write = (unsigned char *) &config_defaults;
    eeprom_writebuf(0x040 , config_write , sizeof(config_defaults));
}
