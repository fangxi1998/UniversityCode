#ifndef GUANGM_H_
#define GUANGM_H_
#include "ioCC2530.h"
 //���������ض��� 

#define LED1  P1_0  //����P1_0ΪLED1 
#define LED2  P1_1  //����P1_1ΪLED2 
#define LED_ON  0   //���忪LED
#define LED_OFF 1  //�����LED
/************************��������******************/

extern unsigned char lightdata[4];

void getGuangM(void);

void InitADC(void);
/***********************��������*******************/
#endif