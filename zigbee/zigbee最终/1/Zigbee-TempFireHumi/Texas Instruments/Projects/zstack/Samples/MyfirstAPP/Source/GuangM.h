#ifndef GUANGM_H_
#define GUANGM_H_
#include "ioCC2530.h"
 //数据类型重定义 

#define LED1  P1_0  //定义P1_0为LED1 
#define LED2  P1_1  //定义P1_1为LED2 
#define LED_ON  0   //定义开LED
#define LED_OFF 1  //定义关LED
/************************函数声明******************/

extern unsigned char lightdata[4];

void getGuangM(void);

void InitADC(void);
/***********************函数声明*******************/
#endif