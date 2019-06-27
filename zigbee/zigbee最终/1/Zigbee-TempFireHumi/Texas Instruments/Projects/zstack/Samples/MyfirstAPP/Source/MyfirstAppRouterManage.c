#include "OSAL_MyfirstAppRouter.h"
#include "MyfirstApp.h"
#include "OnBoard.h"
#include "hal_led.h"
#include "DS18B20.h"
#include "GuangM.h"
#include "Basic.h"
#include "fire.h"
#include "hongwai.h"
#include "yanwu1.h"
#include "oled.h"
#define BEEP P2_0
#define  myID  1

unsigned char temh,teml;
unsigned char ch[10];

byte     My_TaskID;
uint8    TransID = 0;
uint8    tmp_msg[9];
//uint8    light_data[2]; 
uint8    light=0;

//volatile static 
uint8 temperature=0, humi=0;
uint16 uTempValue, uHumiValue;
float fTempValue, fHumiValue;


uint8    fire1=0;
afAddrType_t   multi_DstAddr;
afAddrType_t   Single_DstAddr;

//���˵�ǰ�ڵ������״̬�����ǽ�����ʼ��Ϊ'δ������'
devStates_t  NwkState = DEV_INIT;

void My_Task_Process_MSG ( afIncomingMSGPacket_t *msg );
void Send_Message(void);

//*************************************************
//������Ķ˵��������������˴�������Ϊ ZigBee Ӧ�ó�������������Ϣ
//���ǽ����ڳ�ʼ��������Ϊ����ֵ��Ȼ����ע�ᵽӦ�ó������С�
endPointDesc_t   My_EndPoint_Desc;


//������һ���� ID ���б� �� �����й��ڴ�����Ĵض���Ҫ�ڴ˶���
const uint16 My_InCluster_List[MY_ENDPOINT_MAX_OUTCLUSTERS] =
{ 
  CLUSTER_1_ID,
  CLUSTER_2_ID,
  CLUSTER_3_ID,
  CLUSTER_4_ID
};

const uint16 My_OutCluster_List[MY_ENDPOINT_MAX_INCLUSTERS] =
{ 
  CLUSTER_1_ID,
  CLUSTER_2_ID,
  CLUSTER_3_ID,
  CLUSTER_4_ID
};

//�˶˵�ļ��������������˴������һЩ������Ϣ
const SimpleDescriptionFormat_t    My_EndPoint_SimpleDesc  =
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
     

//********************************************************
void My_Task_Init( byte task_id )
{
  
    My_TaskID = task_id;

    //���õ�����Ϣ
    Single_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
    Single_DstAddr.endPoint = MY_ENDPOINT_NO;//15
    Single_DstAddr.addr.shortAddr = 0x0000;//Э����Ĭ�϶̵�ַΪ0x0000
    
    My_EndPoint_Desc.endPoint = MY_ENDPOINT_NO; //15
    My_EndPoint_Desc.task_id = &My_TaskID;//�û�����ID
    My_EndPoint_Desc.simpleDesc = 
        (SimpleDescriptionFormat_t*)&My_EndPoint_SimpleDesc;
    My_EndPoint_Desc.latencyReq = noLatencyReqs;

    afRegister(&My_EndPoint_Desc);
    
    //InitADC();
    // P2INP&=~0X01;//������ģʽ
  //P2DIR|=0X01;//�ĸ������
  //P2SEL&=~0X01;//ͨ��p1.0 p1.1 p1.2 p1.3 
  //BEEP=1;
    
    
}

//**********************************************************
UINT16 My_Task_Process_Event(byte task_id,UINT16 events)
{    //float light;
     //unsigned char adcdata[]="00.0% ";
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
                if ( NwkState == DEV_END_DEVICE || NwkState == DEV_ROUTER )
                {  
                    osal_start_timerEx(My_TaskID, TMP_MSG_EVT_ID, 4000);
                   // osal_start_timerEx(My_TaskID, FIRE_MSG_EVT_ID, 1000);//����OSAL��ʱ������ʱ�������־
                }
                break;
            case AF_INCOMING_MSG_CMD:  //ģ����յ�������Ϣ�¼�
                 My_Task_Process_MSG( MSGpkt );
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
    
    //�����¶�ֵ���¼�
  if(events & TMP_MSG_EVT_ID)  
    {
       
        DS18B20_SendConvert();
        DS18B20_GetTem();
        getGuangM();
           
        tmp_msg[0] = myID;
        tmp_msg[1] = sensor_data_value[1];
        tmp_msg[2] = sensor_data_value[0];
        tmp_msg[3] =lightdata[0];//ʮλ
        tmp_msg[4] = lightdata[1];//��λ
        tmp_msg[5] =lightdata[3];//С��λ 

        
        io_init();
        getfire();
        tmp_msg[6]=_a[0];
        
        io_inithongwai();
        gethongwai();
        tmp_msg[7]=_b[0];
        
        getyanwu();
        tmp_msg[8]=_data[0];
        
        init_oled();
        teml = tmp_msg[2];
              //��ȡ�¶ȸ�λ
        temh = tmp_msg[1];
        if((temh/10%10==0)&&(temh/100==0))
              ch[4]=' ';
              else ch[4]=temh/10%10+0x30;

              ch[5]=temh%10+0x30;
              //if(((ch[4]-'0')*10+(ch[5]-'0'))>=32)
                //BEEP=0;
              //else
                //BEEP=1;

         
        Send_Message();
        HalLedBlink(HAL_LED_2,3,50,300);
        osal_start_timerEx(My_TaskID, TMP_MSG_EVT_ID, (2000+myID) );
        
        return (events ^ TMP_MSG_EVT_ID);
        
    }

    
     //�رշ��������¼�
    if(events & BEEP_OFF_EVT_ID) 
    {
        BEEP_OFF;
    }
     
    return 0; 
}

//������յ�������
void My_Task_Process_MSG ( afIncomingMSGPacket_t *msg )
{
    switch ( msg->clusterId )
    {
         break;
    case CLUSTER_1_ID :

         
    case CLUSTER_2_ID:
         if(  ('O' == msg->cmd.Data[0])&&
              ('P' == msg->cmd.Data[1])&&  
              ('E' == msg->cmd.Data[2])&&
              ('N' == msg->cmd.Data[3])    )
           
           
         {  HalLedBlink(HAL_LED_2,4,50,300);
            BEEP_ON;
            
            osal_start_timerEx(My_TaskID, BEEP_OFF_EVT_ID, 1000 );
         }
         else if(  ('O' == msg->cmd.Data[0])&&
                 ('N' == msg->cmd.Data[1])   ){
                 
                 OLED=1;
                 
                 }
         else if(  ('C' == msg->cmd.Data[0])&&
              ('L' == msg->cmd.Data[1])&&  
              ('O' == msg->cmd.Data[2])&&
              ('S' == msg->cmd.Data[3]) &&
              ('E' == msg->cmd.Data[4])   )
           
           {
                 
                 OLED=0;
                 
                 }

         break;
      case CLUSTER_3_ID:
         if(  ('O' == msg->cmd.Data[0])&&
              ('N' == msg->cmd.Data[1]))
           
           
         { 
           
           OLED=1;
         }

         break;
          case CLUSTER_4_ID:
         if(  ('C' == msg->cmd.Data[0])&&
              ('L' == msg->cmd.Data[1])&&  
              ('O' == msg->cmd.Data[2])&&
              ('S' == msg->cmd.Data[3])&& 
              ('E' == msg->cmd.Data[4]))
           
           
         { 
            OLED=0;
         }

         break;
         
         
         
    default:  break;    
    }
}

void Send_Message(void)
{
    AF_DataRequest( &Single_DstAddr,                //���͵�ַģʽ
                    &My_EndPoint_Desc,              //�˵�������
                    CLUSTER_1_ID,                   //��ID
                    //(byte)osal_strlen(tmp_msg)+1,   //���ͳ���
                    11,
                    (byte *)tmp_msg,                //��������
                    & TransID,                      //֡���
                    AF_DISCV_ROUTE,                 //����·��
                    AF_DEFAULT_RADIUS);             //·�ɰ뾶��Ĭ��16����
}






