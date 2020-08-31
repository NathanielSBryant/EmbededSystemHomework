/*********************************************
    *vpd.c

    *SER486 Project 2
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *VPD class that holds some basic information of the device

 **********************************************/

#include "vpd.h"
#include "eeprom.h"
#include "util.h"






struct vpd_struct vpd_default= {
    .token = "SER" ,
    .model = "Nathaniel" ,
    .manufacturer = "Bryant" ,
    .serial_number = "BL3" ,
    .manufactur_date = 0 ,
    .mac_address = {(0x4E & 0xFE) , 0x41 , 0x54 , 0x42 , 0x52 , 0x59 } ,
    .country_of_origin = "USA" ,
    .checksum = 0
    };


/**********************************
*
* void vpd_init()
*
*
* Inits the vpd struct by reading eeprom at 0x00
* if data fails a check sum data will be set as default
*
* arguments:
*
* Changes:
*
**********************************/
void vpd_init()
{


    //So what I'm doing here is crazy I'll explain
    //How the strucut is structured there is no blank room
    //I can just feed it the raw eeprom data and make it happy
    while(eeprom_isbusy()){};
    unsigned char * vpd_read;
    vpd_read = (unsigned char *) &vpd;
    eeprom_readbuf(0x00 , vpd_read , sizeof(vpd));
    if(!vpd_is_data_valid())
    {
        vpd_write_defaults();
        vpd_read = (unsigned char *) &vpd;
        eeprom_readbuf(0x00 , vpd_read , sizeof(vpd));
    }



}
/**********************************
*
* int vpd_is_data_valid()
*
*
* Checks if the VPD struct is correct
* by checksuming and the token
*
* arguments:
*
* Returns:
*   1 if data is valid 0 if it is not
*
**********************************/
int vpd_is_data_valid()
{
    char * test = "SER";

    int ii;
    for(ii =0 ; ii < 3 ; ii++)
    {
        if(test[ii] != vpd.token[ii])
        {
            return 0;
        }

    }


    return is_checksum_valid((unsigned char *)&vpd , sizeof(vpd));

}


/**********************************
*
* void vpd_write_defaults()
*
*
* Sets the default values in eeprom for vpd
*
* arguments:
*
* Returns:
*
*
**********************************/
void vpd_write_defaults()
{
    update_checksum((unsigned char *) &vpd_default , sizeof(vpd_default));
    unsigned char * vpd_write;
    vpd_write = (unsigned char *) &vpd_default;
    eeprom_writebuf(0x00 , vpd_write , sizeof(vpd_default));
}

