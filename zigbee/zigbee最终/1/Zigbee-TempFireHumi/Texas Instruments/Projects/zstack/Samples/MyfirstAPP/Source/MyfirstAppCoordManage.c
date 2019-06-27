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


byte     My_TaskID;   //�û�����ID
uint8    TransID=0;   //���ͺ����õ�֡������


//unsigned char changeline[2] ={0x0A,0x0D};
uint8    tmp_data1[10];
uint8    tmp_data2[10];
uint8    tmp_data3[10];
uint16   Short_Addr_List[31];
//afAddrType_t   multi_DstAddr;  //Ⱥ�� ���͵�ַģʽ
afAddrType_t   Single_DstAddr; //���� ���͵�ַģʽ

//���˵�ǰ�ڵ������״̬�����ǽ�����ʼ��Ϊ'δ������'
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
//������ļ��������������˴������һЩ������Ϣ

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
//������Ķ˵��������������˴�������Ϊ ZigBee Ӧ�ó�������������Ϣ
//���ǽ����ڳ�ʼ��������Ϊ����ֵ��Ȼ����ע�ᵽӦ�ó������С�
endPointDesc_t   My_EndPoint_Desc;

//********************************************************

void My_Task_Init( byte task_id )
{
  
    My_TaskID = task_id;
    //���ù㲥Ŀ�ĵ�ַ
    //multi_DstAddr.addrMode = (afAddrMode_t)AddrBroadcast;//���ù㲥��ַģʽ
    //multi_DstAddr.endPoint = MY_ENDPOINT_NO;
    //multi_DstAddr.addr.shortAddr = 0xffff;//���ù㲥��ַĿ�ĵ�ַ�̵�ַ
    //���õ�����Ϣ,��ô����·�����ڵ�Ķ̵�ַ
    Single_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
    Single_DstAddr.endPoint = MY_ENDPOINT_NO;
    My_EndPoint_Desc.endPoint = MY_ENDPOINT_NO;//15
    My_EndPoint_Desc.task_id = &My_TaskID;
    My_EndPoint_Desc.simpleDesc =
        (SimpleDescriptionFormat_t*)&My_EndPoint_SimpleDesc;
    My_EndPoint_Desc.latencyReq = noLatencyReqs;

    afRegister( &My_EndPoint_Desc );//��AF��ע��Ӧ�ö���һ���˵㣩 
    
    InitUART();
   
}

//**********************************************************
UINT16 My_Task_Process_Event(byte task_id,UINT16 events)
{    
    //��һ����Ϣ�����͸�����ʱ,SYS_EVENT_MSG,�¼��ᱻ���ݸ����� 
    //��ʾ��һ����Ϣ�ȴ�����
    afIncomingMSGPacket_t *MSGpkt;
    
    if ( events & SYS_EVENT_MSG )
    {
        //����Ϣ������ȡ����Ϣ
        MSGpkt = (afIncomingMSGPacket_t *)osal_msg_receive(My_TaskID);
        while ( MSGpkt )
        {
            switch ( MSGpkt->hdr.event )
            {
                /*
                ���豸�ɹ����������Ժ� ZigBee �豸����ZDO����������Ѿ���Ӧ�ó�������ע���������
                ��Ҳ������Ϊ ZigBee ��Ӧ�ó��������ڵ����񣩷���һ��ZDO_STATE_CHANGE��Ϣ����Ϣ��״
                ָ̬ʾ�˵�ǰ�����״̬��
                */
            case ZDO_STATE_CHANGE://����״̬�ı��¼�
                
                 NwkState = (devStates_t)MSGpkt->hdr.status;
                if (( NwkState == DEV_ZB_COORD )||( NwkState == DEV_END_DEVICE ))
                {  
                   
                    osal_start_timerEx(My_TaskID, UART_DATA_EVT_ID, 5000);
                    //HalLedSet(HAL_LED_2,HAL_LED_MODE_ON );
                }
                break;
            case AF_INCOMING_MSG_CMD:  //ģ����յ�������Ϣ�¼�
                 My_Task_Process_MSG ( MSGpkt );//������յ�������
                 break; 
            case KEY_CHANGE://�����¼�
               
                 break;
           
            default:
                 break;
            }
            //�ͷ���Ϣ���ڵ���Ϣ������
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

//������յ�������
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
              //��ȡ�¶ȸ�λ
              temh = tmp_data1[1];
              /*teml = tmp_data2[2];
              //��ȡ�¶ȸ�λ
              temh = tmp_data2[1];*/

              ch[0] ='1';
              ch[1] = ' ';

              if(temh & 0x80)            //�ж������¶�
              {
              ch[2]='-';              //���λΪ��
              }
              else ch[2]='+';

              if(temh/100==0)
              ch[3]=' ';
              else 
              ch[3]=temh/100+0x30;      //+0x30 Ϊ�� 0~9 ASCII��

              if((temh/10%10==0)&&(temh/100==0))
              ch[4]=' ';
              else ch[4]=temh/10%10+0x30;

              ch[5]=temh%10+0x30;
              ch[6]='.';

              ch[7]=teml+0x30;// С������
              
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
              //��ȡ�¶ȸ�λ
              temh1 = tmp_data2[1];
              /*teml = tmp_data2[2];
              //��ȡ�¶ȸ�λ
              temh = tmp_data2[1];*/

              chn[0] ='2';
              chn[1] = ' ';

              if(temh & 0x80)            //�ж������¶�
              {
              chn[2]='-';              //���λΪ��
              }
              else chn[2]='+';

              if(temh1/100==0)
              chn[3]=' ';
              else 
              chn[3]=temh1/100+0x30;      //+0x30 Ϊ�� 0~9 ASCII��

              if((temh1/10%10==0)&&(temh1/100==0))
              chn[4]=' ';
              else chn[4]=temh1/10%10+0x30;

              chn[5]=temh1%10+0x30;
              chn[6]='.';

              chn[7]=teml1+0x30;// С������
              
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
   
    
    
    AF_DataRequest( &Single_DstAddr,                //���͵�ַģʽ
                    &My_EndPoint_Desc,              //�˵�������
                    CLUSTER_2_ID,                   //��ID
                    (byte)osal_strlen(tmp_msg)+1,   //���ͳ���
                    (byte *)tmp_msg,                //��������
                    & TransID,                      //֡���
                    AF_DISCV_ROUTE,                 //����·��
                    AF_DEFAULT_RADIUS);             //·�ɰ뾶��Ĭ��16����
  HalLedBlink(HAL_LED_4,2,10,200);
  
    /*multi_DstAddr.addr.shortAddr = 0xffff;//���ù㲥��ַĿ�ĵ�ַ�̵�ַ
     AF_DataRequest( &multi_DstAddr,                //���͵�ַģʽ
                    &My_EndPoint_Desc,              //�˵�������
                    CLUSTER_2_ID,                   //��ID
                    (byte)osal_strlen(tmp_msg)+1,   //���ͳ���
                    (byte *)tmp_msg,                //��������
                    & TransID,                      //֡���
                    AF_DISCV_ROUTE,                 //����·��
                    AF_DEFAULT_RADIUS);             //·�ɰ뾶��Ĭ��16����
  HalLedBlink(HAL_LED_4,2,10,200);
  */
    
  
}

void Send_LEDON_Msg(uint16 ShortAddr)
{
    uint8 tmp_msg1[] = "ON";
    //Single_DstAddr.addr.shortAddr = MY_ENDPOINT_NO;
   Single_DstAddr.addr.shortAddr = ShortAddr;
   
    
    
    AF_DataRequest( &Single_DstAddr,                //���͵�ַģʽ
                    &My_EndPoint_Desc,              //�˵�������
                    CLUSTER_2_ID,                   //��ID
                    (byte)osal_strlen(tmp_msg1)+1,   //���ͳ���
                    (byte *)tmp_msg1,                //��������
                    & TransID,                      //֡���
                    AF_DISCV_ROUTE,                 //����·��
                    AF_DEFAULT_RADIUS);             //·�ɰ뾶��Ĭ��16����
  HalLedBlink(HAL_LED_4,2,10,200);
  
 
    
  
}

void Send_LEDClOSE_Msg(uint16 ShortAddr)
{
    uint8 tmp_msg2[] = "CLOSE";
    //Single_DstAddr.addr.shortAddr = MY_ENDPOINT_NO;
   Single_DstAddr.addr.shortAddr = ShortAddr;
   
    
    
    AF_DataRequest( &Single_DstAddr,                //���͵�ַģʽ
                    &My_EndPoint_Desc,              //�˵�������
                    CLUSTER_2_ID,                   //��ID
                    (byte)osal_strlen(tmp_msg2)+1,   //���ͳ���
                    (byte *)tmp_msg2,                //��������
                    & TransID,                      //֡���
                    AF_DISCV_ROUTE,                 //����·��
                    AF_DEFAULT_RADIUS);             //·�ɰ뾶��Ĭ��16����
  HalLedBlink(HAL_LED_4,2,10,200);
  
    
    
  
}