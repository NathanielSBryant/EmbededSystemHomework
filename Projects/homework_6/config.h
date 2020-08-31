#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED
struct config_struct { //The config struct data strucutre
    char token[4];
    unsigned int hi_alarm;
    unsigned int hi_warn;
    unsigned int lo_alarm;
    unsigned int lo_warn;
    char static_ip[4];
    char use_static_ip;
    char unsigned checksum;

};



struct config_struct config;//Public config file


void config_init(); /* Reads the config information from the EEPROM  */
void config_update(); /* Updates any changes from the config information*/
void config_set_modified(); /* Sets the modifed flag for update*/
int config_is_data_valid(); /* Check sums the data and the token to see if data is intact */
void config_write_defaults(); /* Writes the default values for the config */

#endif // CONFIG_H_INCLUDED
