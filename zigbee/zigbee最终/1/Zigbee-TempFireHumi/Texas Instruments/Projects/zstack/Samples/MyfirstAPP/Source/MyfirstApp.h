#ifndef _MyfirstApp_H_
#define _MyfirstApp_H_


//自己添加
#define  MY_ENDPOINT_NO              15
#define  MY_ENDPOINT_PROFID          0x0F07
#define  MY_ENDPOINT_DEVICEID        0x0002
#define  MY_ENDPOINT_DEVICE_VERSION  0
#define  MY_ENDPOINT_FLAGS           0
#define  MY_ENDPOINT_MAX_INCLUSTERS    4
#define  MY_ENDPOINT_MAX_OUTCLUSTERS   4

#define  CLUSTER_1_ID                3
#define  CLUSTER_2_ID                4
#define  CLUSTER_3_ID                5
#define  CLUSTER_4_ID                6

#define  TMP_MSG_EVT_ID             0x0001  
#define  BEEP_OFF_EVT_ID            0x0002 
#define  UART_DATA_EVT_ID           0x0004

//增加的火焰传感器事件
#define  FIRE_MSG_EVT_ID           0x0008

//增加的光照度传感器事件
//#define  LIGHT_MSG_EVT_ID          0x0010

#define  BEEP_ON                    P2DIR |= 0x01; P2_0 = 0

#define  BEEP_OFF                   P2_0 = 1; P2DIR &= 0xFE

#define uint unsigned int



#endif