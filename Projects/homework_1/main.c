//AUTHOR: Nathaniel Bryant
//COURSE: SER 486
//ASSIGNMENT: Homework Assignment (Module 1)


#include <avr/io.h>
#include "uart.h"

//Takes a string and prints it out to the uart 1 char at a time
void writestr(char * charArray)
{
    char * seeker;//Creates a seeker point to not destory the pointer of the string
    seeker = charArray;

    //Loop will run until a null terminateor is found
    while(*(seeker) != '\0')
    {

        uart_writechar(*(seeker));
        //Inmmcrements the next element
        seeker++;
    }


}

void printNumber(int numb) //Takes the number of bytes the size of a data type and returns it in bits
{


    switch (numb)
    {

        case 1: //One Byte
            writestr("8 bits\n");
        break;

        case 2: //Two Bytes
            writestr("16 bits\n");
        break;

        case 3: //Three Bytes
            writestr("24 bits\n");
        break;

        case 4: //Four Bytes
            writestr("32 bits\n");
        break;
    }

}


int main(void)
{

    uart_init();//Inits uart
    writestr("Hello World from Atmega328\n");
    writestr("SER486 -- Homework Assignment 1\n");
    writestr("Nathaniel Bryant\n");
    writestr("char size (bits) = ");
    printNumber(sizeof(char));
    writestr("int size (bits) = ");
    printNumber(sizeof(int));
    writestr("long size (bits) = ");
    printNumber(sizeof(long));


    while(1) //needed by assignment
   {
    }
    return 0;//How did you get here
}
