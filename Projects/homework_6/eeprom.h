#ifndef EEPROM_H_INCLUDED
#define EEPROM_H_INCLUDED

void eeprom_writebuf(unsigned int addr , unsigned char * buf , unsigned char dsize); //Writes the data to the eeprom
void eeprom_readbuf(unsigned int addr , unsigned char * buf , unsigned char dsize); //reads data from the eeprom
int eeprom_isbusy(); // Is the eeprom busy


#endif // EEPROM_H_INCLUDED
