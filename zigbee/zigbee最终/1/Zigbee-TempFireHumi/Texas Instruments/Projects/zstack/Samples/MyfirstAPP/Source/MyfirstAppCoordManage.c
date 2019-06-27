#include <string.h>
#include "OSAL_MyfirstAppCoord.h"
#include "MyfirstApp.h"
#include "OnBoard.h"
#include "hal_led.h"
#include "hal_uart.h"
#include "hal_lcd.h"
#define BEEP P2_0

unsigned char ch[10];
unsigned char chn[10];
unsigned char temh,teml;
unsigned char temh1,teml1; char *ch1;


byte     My_TaskID;   //用户任务ID
uint8    TransID=0;   //发送函数用的帧计数器


//unsigned char changeline[2] ={0x0A,0x0D};
uint8    tmp_data1[10];
uint8    tmp_data2[10];
uint8    tmp_data3[10];
uint16   Short_Addr_List[31];
//afAddrType_t   multi_DstAddr;  //群发 发送地址模式
afAddrType_t   Single_DstAddr; //单播 发送地址模式

//存了当前节点的网络状态，我们将他初始化为'未加入网'
devStates_t  NwkState = DEV_INIT;

void My_Task_Process_MSG ( afIncomingMSGPacket_t *msg );

static void InitUART(void);
void UART_CallBack( uint8 port,uint8 event);
void Send_Beep_Msg(uint16 ShortAddr);
void Send_LEDON_Msg(uint16 ShortAddr);
void Send_LEDClOSE_Msg(uint16 ShortAddr);

//**************************************************

const uint16 My_InCluster_List[MY_ENDPOINT_MAX_OUTCLUSTERS]=
{  
  CLUSTER_1_ID,
  CLUSTER_2_ID,
  CLUSTER_3_ID,
  CLUSTER_4_ID
};

const uint16 My_OutCluster_List[MY_ENDPOINT_MAX_INCLUSTERS]=
{ 
  CLUSTER_1_ID,
  CLUSTER_2_ID,
  CLUSTER_3_ID,
  CLUSTER_4_ID
};
//此任务的简单描述，它保存了此任务的一些基本信息

const SimpleDescriptionFormat_t    My_EndPoint_SimpleDesc=
{
     MY_ENDPOINT_NO,
     MY_ENDPOINT_PROFID,
     MY_ENDPOINT_DEVICEID,
     MY_ENDPOINT_DEVICE_VERSION,
     MY_ENDPOINT_FLAGS,
     MY_ENDPOINT_MAX_INCLUSTERS,
     (uint16*)My_InCluster_List,
     MY_ENDPOINT_MAX_OUTCLUSTERS,
     (uint16*)My_OutCluster_List
};

//*************************************************
//此任务的端点描述，它定义了此任务作为 ZigBee 应用程序对象的所有信息
//我们将会在初始化函数中为它赋值。然后将他注册到应用程序框架中。
endPointDesc_t   My_EndPoint_Desc;

//********************************************************

void My_Task_Init( byte task_id )
{
  
    My_TaskID = task_id;
    //设置广播目的地址
    //multi_DstAddr.addrMode = (afAddrMode_t)AddrBroadcast;//设置广播地址模式
    //multi_DstAddr.endPoint = MY_ENDPOINT_NO;
    //multi_DstAddr.addr.shortAddr = 0xffff;//设置广播地址目的地址短地址
    //设置单播信息,怎么设置路由器节点的短地址
    Single_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
    Single_DstAddr.endPoint = MY_ENDPOINT_NO;
    My_EndPoint_Desc.endPoint = MY_ENDPOINT_NO;//15
    My_EndPoint_Desc.task_id = &My_TaskID;
    My_EndPoint_Desc.simpleDesc =
        (SimpleDescriptionFormat_t*)&My_EndPoint_SimpleDesc;
    My_EndPoint_Desc.latencyReq = noLatencyReqs;

    afRegister( &My_EndPoint_Desc );//在AF层注册应用对象（一个端点） 
    
    InitUART();
   
}

//**********************************************************
UINT16 My_Task_Process_Event(byte task_id,UINT16 events)
{    
    //当一个消息被发送给任务时,SYS_EVENT_MSG,事件会被传递给任务 
    //表示有一个消息等待处理。
    afIncomingMSGPacket_t *MSGpkt;
    
    if ( events & SYS_EVENT_MSG )
    {
        //从消息队列中取出消息
        MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive(My_TaskID);
        while ( MSGpkt )
        {
            switch ( MSGpkt->hdr.event )
            {
                /*
                当设备成功加入网络以后， ZigBee 设备对象（ZDO）会给所有已经在应用程序框架中注册过的任务
                （也就是作为 ZigBee 的应用程序对象存在的任务）发送一个ZDO_STATE_CHANGE消息，消息的状
                态指示了当前网络的状态。
                */
            case ZDO_STATE_CHANGE://网络状态改变事件
                
                 NwkState = (devStates_t)MSGpkt->hdr.status;
                if (( NwkState == DEV_ZB_COORD )||( NwkState == DEV_END_DEVICE ))
                {  
                   
                    osal_start_timerEx(My_TaskID, UART_DATA_EVT_ID, 5000);
                    //HalLedSet(HAL_LED_2,HAL_LED_MODE_ON );
                }
                break;
            case AF_INCOMING_MSG_CMD:  //模块接收到数据信息事件
                 My_Task_Process_MSG ( MSGpkt );//处理接收到的数据
                 break; 
            case KEY_CHANGE://按键事件
               
                 break;
           
            default:
                 break;
            }
            //释放消息所在的消息缓冲区
            osal_msg_deallocate( (uint8 *)MSGpkt );
            MSGpkt = (afIncomingMSGPacket_t*)osal_msg_receive(My_TaskID);
        }
        
        return (events ^ SYS_EVENT_MSG); 
    }
    
    if(events & UART_DATA_EVT_ID)
    {
      HalLedBlink(HAL_LED_4,2,10,200);
    
      HalUARTWrite( 0, ch1, 20);
//
//      
//      HalUARTWrite( 0, tmp_data2, 10);
//
//      
//       HalUARTWrite( 0, tmp_data3, 10);

      
      osal_start_timerEx(My_TaskID, UART_DATA_EVT_ID, 2000);
       
      return (events ^ UART_DATA_EVT_ID); 
    }
      
    return 0;
   
}

//处理接收到的数据
void My_Task_Process_MSG ( afIncomingMSGPacket_t *msg )
{  
    uint8 i;    
   
    switch ( msg->clusterId )
    {  
    case CLUSTER_1_ID:
            switch(msg->cmd.Data[0])
            {
            case 1:
              tmp_data1[0]=1;
              tmp_data1[1]=msg->cmd.Data[1];
              tmp_data1[2]=msg->cmd.Data[2];
              tmp_data1[3]=msg->cmd.Data[3];
              tmp_data1[4]=msg->cmd.Data[4];
              tmp_data1[5]=msg->cmd.Data[5];
              tmp_data1[6]=msg->cmd.Data[6];
              tmp_data1[7]=msg->cmd.Data[7];
              tmp_data1[8]=msg->cmd.Data[8];
              
              teml = tmp_data1[2];
              //获取温度高位
              temh = tmp_data1[1];
              /*teml = tmp_data2[2];
              //获取温度高位
              temh = tmp_data2[1];*/

              ch[0] ='1';
              ch[1] = ' ';

              if(temh & 0x80)            //判断正负温度
              {
              ch[2]='-';              //最高位为正
              }
              else ch[2]='+';

              if(temh/100==0)
              ch[3]=' ';
              else 
              ch[3]=temh/100+0x30;      //+0x30 为变 0~9 ASCII码

              if((temh/10%10==0)&&(temh/100==0))
              ch[4]=' ';
              else ch[4]=temh/10%10+0x30;

              ch[5]=temh%10+0x30;
              ch[6]='.';

              ch[7]=teml+0x30;// 小数部分
              
              ch1[0]=ch[0];
              ch1[1]=ch[4];
              ch1[2]=ch[5];            
              ch1[3]=ch[7];
              ch1[4]=tmp_data1[3];
              ch1[5]=tmp_data1[4];
              ch1[6]=tmp_data1[5];              
              ch1[7]=tmp_data1[6];
              ch1[8]=tmp_data1[7];
              ch1[9]=tmp_data1[8];
              
              //HalUARTWrite( 0, ch1, 10);

              break;
            case 2:
              tmp_data2[0]=2;
              tmp_data2[1]=msg->cmd.Data[1];
              tmp_data2[2]=msg->cmd.Data[2];
              tmp_data2[3]=msg->cmd.Data[3];
              tmp_data2[4]=msg->cmd.Data[4];
              tmp_data2[5]=msg->cmd.Data[5];
              tmp_data2[6]=msg->cmd.Data[6];
              tmp_data2[7]=msg->cmd.Data[7];
              tmp_data2[8]=msg->cmd.Data[8];
               teml1 = tmp_data2[2];
              //获取温度高位
              temh1 = tmp_data2[1];
              /*teml = tmp_data2[2];
              //获取温度高位
              temh = tmp_data2[1];*/

              chn[0] ='2';
              chn[1] = ' ';

              if(temh & 0x80)            //判断正负温度
              {
              chn[2]='-';              //最高位为正
              }
              else chn[2]='+';

              if(temh1/100==0)
              chn[3]=' ';
              else 
              chn[3]=temh1/100+0x30;      //+0x30 为变 0~9 ASCII码

              if((temh1/10%10==0)&&(temh1/100==0))
              chn[4]=' ';
              else chn[4]=temh1/10%10+0x30;

              chn[5]=temh1%10+0x30;
              chn[6]='.';

              chn[7]=teml1+0x30;// 小数部分
              
              ch1[10]=chn[0];
              ch1[11]=chn[4];
              ch1[12]=chn[5];            
              ch1[13]=chn[7];
              ch1[14]=tmp_data2[3];
              ch1[15]=tmp_data2[4];
              ch1[16]=tmp_data2[5];
              ch1[17]=tmp_data2[6];
              ch1[18]=tmp_data2[7];
              ch1[19]=tmp_data2[8];              
              break;
              

             default:  break;
      
             }     
            i = msg->cmd.Data[0];
            Short_Addr_List[i] = msg->srcAddr.addr.shortAddr;
        
            break;

    case CLUSTER_2_ID:
     
           break;    
    default:  break;    
    }
}
//***************************************************

static void InitUART(void)
{
  halUARTCfg_t uartconfig;
  
  uartconfig.configured = TRUE;
  uartconfig.baudRate = HAL_UART_BR_38400;
  uartconfig.flowControl = FALSE;
  uartconfig.flowControlThreshold = 64;
  uartconfig.idleTimeout = 6;
  uartconfig.rx.maxBufSize = 128;
  uartconfig.tx.maxBufSize = 128;
  uartconfig.intEnable = TRUE;
  uartconfig.callBackFunc = UART_CallBack;
  
  HalUARTOpen( 0,&uartconfig );
}

void UART_CallBack( uint8 port,uint8 event)
{
  uint8  slen = 0;
  uint8  sbuf[20];
  uint16 temp = 0;
  
  if( event & HAL_UART_RX_TIMEOUT )
  {
    slen = HalUARTRead( 0, sbuf, 20);
    if(slen)
    {
      if(  ('B' == sbuf[0])&&
           ('E' == sbuf[1])&&
           ('E' == sbuf[2])&&
           ('P' == sbuf[3])   )
      {
          temp = (sbuf[4]-'0')*10 + (sbuf[5]-'0');
          temp =  Short_Addr_List[temp]; 
          if(temp)
          {
            Send_Beep_Msg(temp);         
          }
      }
      
     else if(  ('L' == sbuf[0])&&
           ('E' == sbuf[1])&&
           ('D' == sbuf[2])&&
           ('O' == sbuf[3])
              )
      {
          temp = (sbuf[4]-'0')*10 + (sbuf[5]-'0');
          temp =  Short_Addr_List[temp]; 
          if(temp)
          {
            Send_LEDON_Msg(temp);         
          }
      }
       else if( ('L' == sbuf[0])&&
           ('E' == sbuf[1])&&
           ('D' == sbuf[2])&&
           ('C' == sbuf[3])
              )
      {
          temp = (sbuf[4]-'0')*10 + (sbuf[5]-'0');
          temp =  Short_Addr_List[temp]; 
          if(temp)
          {
            Send_LEDClOSE_Msg(temp);         
          }
      }
      
    }
    
  }
}

void Send_Beep_Msg(uint16 ShortAddr,)
{
    uint8 tmp_msg[] = "OPEN";
    //Single_DstAddr.addr.shortAddr = MY_ENDPOINT_NO;
   Single_DstAddr.addr.shortAddr = ShortAddr;
   
    
    
    AF_DataRequest( &Single_DstAddr,                //发送地址模式
                    &My_EndPoint_Desc,              //端点描述符
                    CLUSTER_2_ID,                   //簇ID
                    (byte)osal_strlen(tmp_msg)+1,   //发送长度
                    (byte *)tmp_msg,                //发送内容
                    & TransID,                      //帧序号
                    AF_DISCV_ROUTE,                 //发现路由
                    AF_DEFAULT_RADIUS);             //路由半径（默认16级）
  HalLedBlink(HAL_LED_4,2,10,200);
  
    /*multi_DstAddr.addr.shortAddr = 0xffff;//设置广播地址目的地址短地址
     AF_DataRequest( &multi_DstAddr,                //发送地址模式
                    &My_EndPoint_Desc,              //端点描述符
                    CLUSTER_2_ID,                   //簇ID
                    (byte)osal_strlen(tmp_msg)+1,   //发送长度
                    (byte *)tmp_msg,                //发送内容
                    & TransID,                      //帧序号
                    AF_DISCV_ROUTE,                 //发现路由
                    AF_DEFAULT_RADIUS);             //路由半径（默认16级）
  HalLedBlink(HAL_LED_4,2,10,200);
  */
    
  
}

void Send_LEDON_Msg(uint16 ShortAddr)
{
    uint8 tmp_msg1[] = "ON";
    //Single_DstAddr.addr.shortAddr = MY_ENDPOINT_NO;
   Single_DstAddr.addr.shortAddr = ShortAddr;
   
    
    
    AF_DataRequest( &Single_DstAddr,                //发送地址模式
                    &My_EndPoint_Desc,              //端点描述符
                    CLUSTER_2_ID,                   //簇ID
                    (byte)osal_strlen(tmp_msg1)+1,   //发送长度
                    (byte *)tmp_msg1,                //发送内容
                    & TransID,                      //帧序号
                    AF_DISCV_ROUTE,                 //发现路由
                    AF_DEFAULT_RADIUS);             //路由半径（默认16级）
  HalLedBlink(HAL_LED_4,2,10,200);
  
 
    
  
}

void Send_LEDClOSE_Msg(uint16 ShortAddr)
{
    uint8 tmp_msg2[] = "CLOSE";
    //Single_DstAddr.addr.shortAddr = MY_ENDPOINT_NO;
   Single_DstAddr.addr.shortAddr = ShortAddr;
   
    
    
    AF_DataRequest( &Single_DstAddr,                //发送地址模式
                    &My_EndPoint_Desc,              //端点描述符
                    CLUSTER_2_ID,                   //簇ID
                    (byte)osal_strlen(tmp_msg2)+1,   //发送长度
                    (byte *)tmp_msg2,                //发送内容
                    & TransID,                      //帧序号
                    AF_DISCV_ROUTE,                 //发现路由
                    AF_DEFAULT_RADIUS);             //路由半径（默认16级）
  HalLedBlink(HAL_LED_4,2,10,200);
  
    
    
  
}