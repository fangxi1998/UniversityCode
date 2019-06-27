#include <ioCC2530.h>
#include "fire.h"
#include "hal_types.h"
#define uint unsigned int
#define uchar unsigned char

#define led1 P1_0
#define led2 P1_1
#define led3 P1_2
#define led4 P1_3

uint8 fire = 0;
uchar a,b;
unsigned char _a[3];

//io���ⲿ�жϳ�ʼ��
void io_init(void)
{
  //1.4 1.5 Ϊ����
  P1DIR &= ~((1 << 4)|(1 << 5));  //  (0x00010000 | 0x00100000)=> 0x00110000  ~=> 0x11001111   //��Ϊ����
  P1SEL &= ~((1 << 4)|(1 << 5));
  
}
void getfire(void)   
{
    a=P1;
    //��4 5 ��Ϊ1
    b=(~a&0x30);   // 0x00110000 & 0x00110000  = 0x00110000
    if(b)  
      _a[0]='1'; //�л���
    else 
      _a[0]='0'; //�޻���
 }
