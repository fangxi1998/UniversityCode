#include "ioCC2530.h"
#include "oled.h"
#include "hal_types.h"

#define uint unsigned int
#define uchar unsigned char

#define OLED P1_5


void init_oled(void);


void init_oled()
{
   P1DIR |= 0x20; 
   //P1_5=0;
}
