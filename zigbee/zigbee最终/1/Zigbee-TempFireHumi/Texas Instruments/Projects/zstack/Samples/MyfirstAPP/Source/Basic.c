/***********************************************************
**  FileName:         Basic.c
**  Introductions:    Sunplusapp CC2530 ZigBee Node Basic Functions & Options
**  Last Modify time: 2013.06.13
**  Modify:           ������ʵ������LED��Ÿ��ģ���ӿ���LED��˸�ĺ���
**  Author:           GuoZhenjiang	<zhenjiang.guo@sunplusapp.com>
***********************************************************/

#include "Basic.h"

/***********************************************************
**  ��������: SystemClockSet
**  ʵ�ֹ���: ϵͳʱ������
**  ��ڲ���: RTC_Clk:  RTCʱ��Դѡ��( CPU_32kHz_RC �� CPU_32kHz_XOC)
**            CPU_Clk:  CPUʱ��Դѡ��( CPU_16MHz_RC �� CPU_32MHz_XOC)
**            T_Spd:    ��ʱ��ʱ��ԴԤ��Ƶ���ã�TSPD_x����ʾȡCPUʱ��Դ��1/x��
**            CPU_Spd:  CPUʱ��ԴԤ��Ƶ���ã� CLKSPD_x����ʾȡCPUʱ��Դ��1/x��
**  ���ؽ��: None
***********************************************************/
void SystemClockSet( ClkSet_t RTC_Clk, ClkSet_t CPU_Clk, ClkSet_t T_Spd, ClkSet_t CPU_Spd )
{
    uint8 SysClockSet;
    SysClockSet = RTC_Clk | CPU_Clk | T_Spd | CPU_Spd;
    //����ϵͳ����ʱ�Ӳ���
    CLKCONCMD = SysClockSet;

    //�ȴ�ʱ���ȶ�
    while( CLKCONSTA != SysClockSet)
        ;
}

/***********************************************************
**  ��������: delay_us
**  ʵ�ֹ���: ΢�뼶������ʱ
**  ��ڲ���: [t]:CPU ��һ��ʱ����;
**  ���ؽ��: None
***********************************************************/
/*
void delay_us(uint16 t)
{
    uint16 i;
    for(i=0; i<t; i++)
        ;
}
*/
/***********************************************************
**  ��������: delay_10ms
**  ʵ�ֹ���: ��ʱ����
**  ��ڲ���: num_10ms:Ҫ��ʱֵ�� 10ms ����;
**  ���ؽ��: None
***********************************************************/
void delay_10ms(uint16 num_10ms)
{
    uint16 i, j, k;
    for(i=0; i<num_10ms; i++)
        for(j=0; j<100; j++)
            for(k=0; k<100; k++)
                ;
}

/***********************************************************
**  ��������: LED_4_5_PortInit
**  ʵ�ֹ���: ��չ���ϵ� LED_D4_D5 �˿ڳ�ʼ��
**  ��ڲ���: None
**  ���ؽ��: None
***********************************************************/
void LED_4_5_PortInit(void)
{
    P1SEL &= ~0X02;
    P2SEL &= ~0X01;

    P1DIR |= 0X02;
    P2DIR |= 0X01;

    LED_4_OFF;
    LED_5_OFF;
}

/***********************************************************
**  ��������: LED_Flash
**  ʵ�ֹ���: LED4 & LED5��˸����
**  ��ڲ���: led:���õ�LED
**            num:��˸����
**            onTime:ÿ����˸����ʱ��10ms��
**            offTime:ÿ����˸Ϩ��ʱ��10ms��
**  ���ؽ��: None
***********************************************************/
void LED_Flash(LED_t led, uint16 num, uint16 onTime, uint16 offTime)
{
    uint16 Num;
    for(Num=0; Num < num; Num++)
    {
        // ����
        switch(led)
        {
        case LED4:  LED_4_ON;   break;
        case LED5:  LED_5_ON;   break;
        case LED45: LED_45_ON;  break;
        default :               break;
        }
        delay_10ms(onTime);
        // Ϩ��
        switch(led)
        {
        case LED4:  LED_4_OFF;  break;
        case LED5:  LED_5_OFF;  break;
        case LED45: LED_45_OFF; break;
        default :               break;
        }
        delay_10ms(offTime);
    }
}

/***********************************************************
**  ��������: SetIOInput
**  ʵ�ֹ���: ���ö˿�Ϊ��ͨ����IO
**  ��ڲ���: group:Port;
**            bit:Bit;
**            pull:(Pull_None:��������; Pull_Up:����; Pull_Down:����;);
**  ���ؽ��: None
***********************************************************/
void SetIOInput(uint8 group, uint8 bit, PullSet_t pull)
{
    switch(group)
    {
    case 0:
        //����Ϊͨ������IO
        P0DIR &= BIT_0(bit); P0SEL &= BIT_0(bit);
        //�����ڲ�����������״̬
        if(Pull_None == pull)
            P0INP |= BIT_1(bit);     //P0INP[7-0]:(0:��������Ч; 1:��Ч;)
        else if(Pull_Up == pull)
        {
            P0INP &= BIT_0(bit);     //P0INP[7-0]:(0:��������Ч; 1:��Ч;)
            P2INP &= BIT_0(5);       //P2INP[5  ]:(0:Port0 ����; 1:Port0 ����;)
        }
        else if(Pull_Up == pull)
        {
            P0INP &= BIT_0(bit);     //P0INP[7-0]:(0:��������Ч; 1:��Ч;)
            P2INP |= BIT_1(5);       //P2INP[5  ]:(0:Port0 ����; 1:Port0 ����;)
        }
        break;
    case 1:
        //����Ϊͨ������IO
        P1DIR &= BIT_0(bit); P1SEL &= BIT_0(bit);
        //�����ڲ�����������״̬
        if(Pull_None == pull)
            P1INP |= BIT_1(bit);     //P1INP[7-2]:(0:��������Ч; 1:��Ч;) P[1-0] д��Ч����Ϊ0.
        else if(Pull_Up == pull)
        {
            P1INP &= BIT_0(bit);     //P1INP[7-2]:(0:��������Ч; 1:��Ч;) P[1-0] д��Ч����Ϊ0.
            P2INP &= BIT_0(6);       //P2INP[6  ]:(0:Port1 ����; 1:Port1 ����;)
        }
        else if(Pull_Up == pull)
        {
            P0INP &= BIT_0(bit);     //P1INP[7-2]:(0:��������Ч; 1:��Ч;) P[1-0] д��Ч����Ϊ0.
            P2INP |= BIT_1(6);       //P2INP[6  ]:(0:Port1 ����; 1:Port1 ����;)
        }
        break;
    case 2:
        //����Ϊͨ������IO
        P2DIR &= BIT_0(bit); P2SEL &= BIT_0(bit);
        //�����ڲ�����������״̬
        if(Pull_None == pull)
            P2INP |= BIT_1(bit);     //P2INP[4-0]:(0:��������Ч; 1:��Ч;)
        else if(Pull_Up == pull)
        {
            P2INP &= BIT_0(bit);     //P2INP[4-0]:(0:��������Ч; 1:��Ч;)
            P2INP &= BIT_0(7);       //P2INP[7  ]:(0:Port2 ����; 1:Port2 ����;)
        }
        else if(Pull_Up == pull)
        {
            P2INP &= BIT_0(bit);     //P2INP[4-0]:(0:��������Ч; 1:��Ч;)
            P2INP |= BIT_1(7);       //P2INP[7  ]:(0:Port2 ����; 1:Port2 ����;)
        }
        break;
    default:
        break;
    }
}

/***********************************************************
**  ��������: SetIOOutput
**  ʵ�ֹ���: ���ö˿�Ϊ��ͨ���IO
**  ��ڲ���: group:Port;
**            bit:Bit;
**  ���ؽ��: None
***********************************************************/
void SetIOOutput(uint8 group, uint8 bit)
{
    switch(group)
    {
        case 0: P0DIR |= BIT_1(bit); P0SEL &= BIT_0(bit); break;
        case 1: P1DIR |= BIT_1(bit); P1SEL &= BIT_0(bit); break;
        case 2: P2DIR |= BIT_1(bit); P2SEL &= BIT_0(bit); break;
        default:    break;
    }
}

/***********************************************************
**  ��������: GetIOLevel
**  ʵ�ֹ���: ��ȡ�˿ڵ�����״̬
**  ��ڲ���: group:Port;
**            bit:Bit;
**  ���ؽ��: (0:Low; 1:High;)
***********************************************************/
uint8 GetIOLevel(uint8 group, uint8 bit)
{
    switch(group)
    {
        case 0: return !!(P0 & (BIT_1(bit)));
        case 1: return !!(P1 & (BIT_1(bit)));
        case 2: return !!(P2 & (BIT_1(bit)));
        default:    break;
    }
    return 0;
}

/***********************************************************
**  ��������: SetIOLevel
**  ʵ�ֹ���: ���ö˿ڵ������ƽ
**  ��ڲ���: group:Port;
**            bit:Bit;
**            value:(0:Low; 1:High);
**  ���ؽ��: None
***********************************************************/
void SetIOLevel(uint8 group, uint8 bit, uint8 value)
{
    switch(group)
    {
      case 0:
          if(value)
            P0 |= BIT_1(bit);
          else
            P0 &= BIT_0(bit);
          break;
      case 1:
          if(value)
            P1 |= BIT_1(bit);
          else
            P1 &= BIT_0(bit);
          break;
      case 2:
          if(value)
            P2 |= BIT_1(bit);
          else
            P2 &= BIT_0(bit);
          break;
      default:
          break;
    }
}

/***********************************************************
**  ��������: IOIntteruptSet
**  ʵ�ֹ���: ���ö˿��жϴ�����ʽ
**  ��ڲ���: group:Port;
**            bit:Bit;
**            trigger:(Rising:�����ش���; Falling:�½��ش���;)
**  ���ؽ��: None
***********************************************************/
void IOIntteruptSet(uint8 group, uint8 bit, IntSel_t trigger)
{
    switch(group)
    {
    case 0:
        IEN1 |= BIT_1(5); //P0���ж�����
        switch(trigger)
        {
            case None:    P0IEN &= BIT_0( bit ); break;   //����λ�ж�����
            case Rising:  P0IEN |= BIT_1( bit );  PICTL &= BIT_0(0); break;
            case Falling: P0IEN |= BIT_1( bit );  PICTL |= BIT_1(0); break;
            default : break;
        }
        break;
    case 1:
        IEN2 |= BIT_1(4); //P1���ж�����
        switch(trigger)
        {
            case None:    P1IEN &= BIT_0( bit ); break;   //����λ�ж�����
            case Rising:
            {
                if( bit <= 3 )
                {
                    P1IEN |= BIT_1( bit );  PICTL &= BIT_0(1); break;
                }
                else if( bit >= 4 )
                {
                    P1IEN |= BIT_1( bit );  PICTL &= BIT_0(2); break;
                }
            }
            case Falling:
            {
                if( bit <= 3 )
                {
                    P1IEN |= BIT_1( bit );  PICTL |= BIT_1(1); break;
                }
                else if( bit >= 4 )
                {
                    P1IEN |= BIT_1( bit );  PICTL |= BIT_1(2); break;
                }
            }
            default : break;
        }
        break;
    case 2:
        IEN2 |= BIT_1(1); //P2���ж�����
        switch(trigger)
        {
            case None:    P2IEN &= BIT_0( bit ); break;   //����λ�ж�����
            case Rising:  P2IEN |= BIT_1( bit );  PICTL &= BIT_0(3); break;
            case Falling: P2IEN |= BIT_1( bit );  PICTL |= BIT_1(3); break;
            default : break;
        }
        break;
    }
}