/***********************************************************
**  FileName:         Basic.h
**  Introductions:    Sunplusapp CC2530 ZigBee Node Basic Functions & Options
**  Last Modify time: 2013.06.13
**  Modify:           ������ʵ������LED��Ÿ��ģ���ӿ���LED��˸�ĺ���
**  Author:           GuoZhenjiang	<zhenjiang.guo@sunplusapp.com>
***********************************************************/

#ifndef __BASIC_H__
#define __BASIC_H__

#include <iocc2530.h>
#include "hal_types.h"
// ��������������
//typedef char int8;
//typedef int int16;
//typedef unsigned int uint16;
//typedef unsigned char uint8;

#define BIT(x)    ( 1 << x  ) //λ����
#define BIT_1(x)  (  BIT(x) ) //λ��1��
#define BIT_0(x)  (~(BIT(x))) //λ��0��

// �˿���Ϊ����ʱ�ڲ�������ѡ��
typedef enum
{
  Pull_None,  //��̬����
  Pull_Up,    //����ʹ��
  Pull_Down,  //����ʹ��
}PullSet_t;

// ��չ���� LED_D8_D9 ����
#define LED_4_ON    do{P2 &= 0XFE;}while(0)
#define LED_5_ON    do{P1 &= 0XFD;}while(0)
#define LED_45_ON   do{LED_4_ON;  LED_5_ON;}while(0)
#define LED_4_OFF   do{P2 |= 0X01;}while(0)
#define LED_5_OFF   do{P1 |= 0X02;}while(0)
#define LED_45_OFF  do{LED_4_OFF;  LED_5_OFF;}while(0)
#define LED_4_TURN  do{P2 ^= 0X01;}while(0)
#define LED_5_TURN  do{P1 ^= 0X02;}while(0)
#define LED_45_TURN do{LED_4_TURN; LED_5_TURN;}while(0)

/***********************************************************
**  CC2530Ƭ�ں���16MHz RC��������32.768kHz RC������
**  δ��ʼ��ϵͳʼ��ʱ��Ĭ��ʹ���ڲ�16MHz��RCʱ��Դ
**  ��ʱ��Ԥ��Ƶ����ٶȲ��ܸ���ϵͳԤ��Ƶ����ٶȣ����������С�
***********************************************************/
typedef enum
{
  // ϵͳʱ��Դѡ����
  CPU_32kHz_RC  = 0X80,
  CPU_32kHz_XOC = 0X00,
  // ϵͳRTCʱ��Դѡ����
  CPU_16MHz_RC  = 0X40,
  CPU_32MHz_XOC = 0X00,
  // ��ʱ��Ԥ��Ƶ���ã���������ֱ�ʾϵͳʱ��Դ�Ķ��ٷ�֮һ
  TSPD_1        = ( 0X00 << 3), //32MHz  @ System Clock = 32MHz;
  TSPD_2        = ( 0X01 << 3), //16MHz  @ System Clock = 32MHz;
  TSPD_4        = ( 0X02 << 3), //8MHz   @ System Clock = 32MHz;
  TSPD_8        = ( 0X03 << 3), //4MHz   @ System Clock = 32MHz;
  TSPD_16       = ( 0X04 << 3), //2MHz   @ System Clock = 32MHz;
  TSPD_32       = ( 0X05 << 3), //1MHz   @ System Clock = 32MHz;
  TSPD_64       = ( 0X06 << 3), //500kHz @ System Clock = 32MHz;
  TSPD_128      = ( 0X07 << 3), //250kHz @ System Clock = 32MHz;
  // ϵͳʱ��Ԥ��Ƶ���ã���������ֱ�ʾϵͳʱ��Դ�Ķ��ٷ�֮һ
  CLKSPD_1      = 0X00, //32MHz  @ System Clock = 32MHz;
  CLKSPD_2      = 0X01, //16MHz  @ System Clock = 32MHz;
  CLKSPD_4      = 0X02, //8MHz   @ System Clock = 32MHz;
  CLKSPD_8      = 0X03, //4MHz   @ System Clock = 32MHz;
  CLKSPD_16     = 0X04, //2MHz   @ System Clock = 32MHz;
  CLKSPD_32     = 0X05, //1MHz   @ System Clock = 32MHz;
  CLKSPD_64     = 0X06, //500kHz @ System Clock = 32MHz;
  CLKSPD_128    = 0X07, //250kHz @ System Clock = 32MHz;
}ClkSet_t;

/***********************************************************
**  CC2530ÿ��ͨ��IO���Ŷ����Բ����жϣ�
***********************************************************/
typedef enum
{
  // �жϴ�����ʽѡ��
  None,     // �ر���Ӧ�ж�
  Rising,   // �����ش���
  Falling,  // �½��ش���
}IntSel_t;

// ���õ�LED
typedef enum
{
    LED4,   // LED_4
    LED5,   // LED_4
    LED45,  // LED_4&LED_5
}LED_t;

//����ϵͳʼ������
#define SYSTEM_CLK_SET_32M_OSC_NOSPD SystemClockSet( CPU_32kHz_XOC, CPU_32MHz_XOC, TSPD_1, CLKSPD_1 )

// ϵͳʼ�����ú���
void SystemClockSet( ClkSet_t RTC_Clk, ClkSet_t CPU_Clk, ClkSet_t T_Spd, ClkSet_t CPU_Spd );
// ������ʱ����
void delay_us(uint16 t);
// Լ10ms��ʱ����
void delay_10ms(uint16 num_10ms);


// ��չ���� LED_4_5 ��ʼ��
void LED_4_5_PortInit(void);
// ��չ���� LED_4_5 ��ʼ��
void LED_Flash(LED_t led, uint16 num, uint16 onTime, uint16 offTime);

//���ö˿�����ģʽ
void SetIOInput(uint8 group, uint8 bit, PullSet_t pull);
// ���ö˿�Ϊ���
void SetIOOutput(uint8 group, uint8 bit);
// ��ȡ�˿�����״̬
uint8 GetIOLevel(uint8 group, uint8 bit);
// ���ö˿������ƽ
void SetIOLevel(uint8 group, uint8 bit, uint8 value);
// ���ö˿��жϴ�����ʽ
void IOIntteruptSet(uint8 group, uint8 bit, IntSel_t trigger);


#endif  //__BASIC_H__