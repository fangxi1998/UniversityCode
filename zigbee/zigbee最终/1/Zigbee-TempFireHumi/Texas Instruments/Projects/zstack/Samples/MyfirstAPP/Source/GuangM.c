#include "GuangM.h"
unsigned char lightdata[4];
 
void InitADC(void){

    P0DIR&=0x7f;
  ADCIF=0;
  ADCH&=0x00;
  APCFG|=0x80;
  ADCCON3=0xb7;
  while(!(ADCCON1&0x80));
/*
  ADCH&=0x00;
  ADCL&=0x00;//寄存器清零
  ADCCFG|=0x80;      // p0.7 为1   1000 0000
  ADCCON3=0xB7;//1011 0111
  ADCCON1=0x30;   //    0011 0000 ST//手动启动模式  
  ADCCON1|=0x40;//0100 0000    
  
*/
}



void getGuangM(void){
 unsigned char send_buf[2];
 unsigned int light;
  float num;
  InitADC();
 

  send_buf[0]=ADCH;
  send_buf[1]=ADCL;
	//1111 1111 1111 11xx->3.3v
    light =(unsigned int)send_buf[1];// 0000 0000 xxxx xxxx
    light|=((unsigned int)send_buf[0])<<8;//左移八位 或运算
    // adc = 0111 1111 1111 1100 = 32764 ->3.3v
    if(light&0x8000)light=0;
    num=light*3.3/32764;//2^14
    //浮点型转换为字符型
    num=(3.3-num)/3.3*100;
    lightdata[0]=(char)(num)/10+0x30;
    lightdata[1]=(char)(num)%10+0x30;
    lightdata[3]=(char)(num*10)%10+0x30;
   
    
    
    
    
  
  
  

}