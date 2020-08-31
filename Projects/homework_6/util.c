/*********************************************
    *util.c

    *SER486 Project 2
    *Spring 2020
    *Written By: Nathaniel Bryant
    *Modified By:

    *util class for checksums

 **********************************************/
#include "util.h"


/**********************************
*
* void update_checksum()
*
*
* updates the checksum of any struct given
*
* arguments:
*   unsigned char * data: The pointer to struct
*   unsigned int dsize: The size of the struct
*
* Returns:
*
*
**********************************/
void update_checksum(unsigned char * data, unsigned int dsize)
{
    //Not orignal code used template from lecture
    unsigned char ii;
    unsigned char sum = 0;

    for (ii = 0 ; ii<dsize-1 ; ii++)
    {
        sum+= data[ii];
    }

    data[dsize-1] = 0 - sum;

}

/**********************************
*
* void is_check_sum_valud()
*
*
* Checks if checksum is valid
*
* arguments:
*   unsigned char * data: The pointer to struct
*   unsigned int dsize: The size of the struct
*
* Returns:
*   1 if checksum is vald 0 if not
*
*
**********************************/
int is_checksum_valid(unsigned char * data , unsigned int dsize)
{
    //Not orignal code used template from lecture
    unsigned char ii;
    unsigned char sum = 0;
    for (ii = 0 ; ii<dsize-1 ; ii++)
    {
        sum+= data[ii];
    }

    return (sum == 0);
}
