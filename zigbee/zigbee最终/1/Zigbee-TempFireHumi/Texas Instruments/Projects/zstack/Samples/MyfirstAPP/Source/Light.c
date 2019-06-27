#include <ioCC2530.h>
#include "light.h"
#include "hal_types.h"


//#include "hal_lcd.h"

//#define uint unsigned int
//#define uchar unsigned char



//#define led1 P1_0
//#define led2 P1_1
//#define led3 P1_2
//#define led4 P1_3

unsigned char temp[2];
unsigned short adc=0;
unsigned char  adc_value =0;
float v;
//uint8 ge,shi;;

//unsigned char ASCII[16] = "0123456789ABCDEF";

//��ʱ�Ӻ���
//void Delay(uint n)  
//{
//     uint tt;
//     for(tt=0;tt<n;tt++);
//     for(tt=0;tt<n;tt++);
//     for(tt=0;tt<n;tt++);
 //    for(tt=0;tt<n;tt++);
 //    for(tt=0;tt<n;tt++);
//}



//LED�Ƴ�ʼ��
//void led_init(void)
//{
 //  //P1Ϊ��ͨ I/O ��
//   P1SEL =0x00; 
//   // P1.0 P1.1 P1.2 P1.3 ���
//   P1DIR = 0x0F;          
   //�ر�LED1
//   led1=1;
   //�ر�LED2
 //  led2=1;
   //�ر�LED3
//   led3=1;
   //�ر�LED4
//   led4=1;
   
//}


/****************************************************************
*�������� ����ʼ��ADC						*
*��ڲ��� ����					        	*
*�� �� ֵ ����							*
*˵    �� ���ο���ѹAVDD��ת��������1/3AVDD			*
****************************************************************/

void InitialAD( void )  
     {
        //P0DIR &= ~(1<<7); 
        ADCH &= 0X00;
        ADCCFG |=  (1<<7);
        ADCCON3 = 0xa7;
        
        ADCCON1 = 0X30;	
    
        //����A/D
        ADCCON1 |= 0X40;	
        

     }

//������
unsigned char Light_GetAdc(void)  
{

  //�ȴ�ADCת�����
      while(!(ADCCON1&0x80));
      
            //ת�����ָʾ
      temp[1] = ADCL;
      temp[0] = ADCH;
            
      adc  =   (unsigned int)temp[1]>>5;
      adc |= ( (unsigned int)temp[0] )<<3;
            
      v = ((float)adc / (float)0x100);
      adc_value= (unsigned char)(100-v*100);
                          
      return adc_value;
      
}


