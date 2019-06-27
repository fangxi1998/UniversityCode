/**************************************************
  * DS18B20����ԭ�ͼ���ر���
  * ����ļ���DS18B20.H
  * ��д���ڣ�2011.1.4
  * �޸���ʷ:
  *   2011.1.4 15:05 �����˲�������
  *   2011.1.5 10:14 �����¶�С�����ֶ�Ӧ��ֵ��
  *
**************************************************/

#ifndef DS18B20_H_
#define DS18B20_H_

/**************************************************
  ���¶���ΪDS18B20֧�ֵ���������
***************************************************/
#include "ioCC2530.h"

#define SEARCH_ROM      0xF0              //����ROM
#define READ_ROM        0x33              //��ROM
#define MATCH_ROM       0x55              //ƥ��ROM(�Ҷ��DS18B20ʱʹ��)
#define SKIP_ROM        0xCC              //����ƥ��ROM(����DS18B20ʱ����)
#define ALARM_SEARCH    0xEC              //��������

#define CONVERT_T       0x44              //��ʼת���¶�
#define WR_SCRATCHPAD   0x4E              //д���
#define RD_SCRATCHPAD   0xBE              //�����
#define CPY_CCTATCHPAD  0x48              //���Ʊ��
#define RECALL_EE       0xB8              //δ����
#define RD_PWR_SUPPLY   0xB4              //����Դ��Ӧ

#define HIGH            1                 //�ߵ�ƽ
#define LOW             0                 //�͵�ƽ

#define DQ            P1_7                //DS18B20����IO��
#define DQ_DIR_OUT    0x80                //DS18B20 IO����
#define CL_DQ()     DQ = LOW              //�������
#define SET_DQ()    DQ = HIGH             //��������
#define SET_OUT()   P1DIR |=  DQ_DIR_OUT  //����IO����,out����IO����Ϊ���
#define SET_IN()    P1DIR &= ~DQ_DIR_OUT  //����IO����,in�豸IO����Ϊ����

//typedef unsigned short uint16;            //���������ض��� 


extern unsigned char sensor_data_value[2];  //����������

extern void delay_nus(unsigned int n);            //��ʱn us����

extern void DS18B20_Write(unsigned char x); //DS18B20д����

extern unsigned char DS18B20_Read(void);    //DS18B20������

extern void DS18B20_Init(void);             //DS18B20��ʼ��/��λ

extern void DS18B20_SendConvert(void);      //����ת���¶�����

extern void DS18B20_GetTem(void);           //DS18B20��ȡ�¶�

#endif
