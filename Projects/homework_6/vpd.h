#ifndef VPD_H_INCLUDED
#define VPD_H_INCLUDED
struct vpd_struct { //Struct that holds all the VPD data

    char token[4];
    char model[12];
    char manufacturer[12];
    char serial_number[12];
    unsigned long manufactur_date;
    unsigned char mac_address[6];
    char country_of_origin[4];
    unsigned char checksum;

};

struct vpd_struct vpd; //Public variable for vpd

void vpd_init();//Inits the data
int vpd_is_data_valid();//Checks if data is correct
void vpd_write_defaults();//Writes the defaults

#endif // VPD_H_INCLUDED
