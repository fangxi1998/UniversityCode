#include "ioCC2530.h"
#include "hongwai.h"
#include "hal_types.h"

#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0
#define PE0PLE P0_4 
unsigned char _b[3];

void Delay(uint);

void io_init(void);

void  Delay(uint k)
{
uint i,j;
for(i = 0;i< k;i++)
   for(j=0;j<k;j++ );
}


void io_inithongwai()
{
   //0.4为输入
  P0DIR &= ~(1 << 4);   //0x0001 0000   0x1110 1111
  P0SEL &= ~(1 << 4);
  
}

void gethongwai(void)   
{
    if(PE0PLE==1)  //关键点
       _b[0]='0';
    else 
       _b[0]='1';
 }