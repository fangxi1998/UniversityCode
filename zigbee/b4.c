#include<wiringSerial.h>
#include<stdio.h>
#include<wiringPi.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

#define LISTEN_PORT 1200
#define MAX_QUE_CONN_NM 5
#define HIGH_TIME 32
int g_nClientNum=0;
int fd;
int s=22;
int wen=0,shi=0;
char data[8];
int pinNumber=7;
int sockfd,client_fd;
	
char beep01[6]="BEEP01";	
char beep02[6]="BEEP02";
char humi[2];
	//char data[8];
void *wenshidu(void* arg);	
void *temp(void *arg);
void *server(void *arg);


typedef unsigned char uint8;
typedef unsigned long uint32;
uint32 databuf;
uint8 readSensorData(void);

pthread_mutex_t g_mutexData;
pthread_mutex_t g_mutexCmd;

int main(){
	wiringPiSetup();
	softPwmCreate(1,22,200);
	pthread_t threadNO;
	pthread_create(&threadNO, NULL, server, NULL);
	
	while(1)
	{

	}

	return 0;
		
}

void *wenshidu(void* arg)
{
	while(1)
	{
		pinMode(pinNumber,OUTPUT);
		digitalWrite(pinNumber,1);
		delay(3000);
		if(readSensorData())
		{
			shi=((databuf>>24)&0xff);
			wen=((databuf>>8)&0xff);
			humi[0]=shi;
			humi[1]=wen;
			databuf=0;
		}
		else
		{
			databuf=0;
		}
	}
}

uint8 readSensorData(void)
{
	uint8 crc;
	uint8 i;

	pinMode(pinNumber,OUTPUT);
	digitalWrite(pinNumber,0);
	delay(25);
	digitalWrite(pinNumber,1);
	pinMode(pinNumber,INPUT);
	pullUpDnControl(pinNumber,PUD_UP);
	delayMicroseconds(27);
	if(digitalRead(pinNumber)==0)
	{
		while(!digitalRead(pinNumber));
		for(i=0;i<32;i++)
		{
			while(digitalRead(pinNumber));
			while(!digitalRead(pinNumber));
			delayMicroseconds(HIGH_TIME);
			databuf*=2;
			if(digitalRead(pinNumber)==1)
			{
				databuf++;
			}
		}
		for(i=0;i<8;i++)
		{
			while(digitalRead(pinNumber));
			while(!digitalRead(pinNumber));
			delayMicroseconds(HIGH_TIME);
			crc*=2;
			if(digitalRead(pinNumber)==1)
			{
				crc++;
			}
		}
		return 1;
	}
	else
	{
		return 0;
	}	
}

void *server(void *arg){
	if((fd=serialOpen("/dev/ttyAMA0",38400))==-1){
		
			printf("Open Error");
		}else{
			printf(" Serial Open Success\n ");
			
		}
	
	
	int sin_size,i;
    struct sockaddr_in server_sockaddr,client_sockaddr;
    int sockfd, client_fd;

   /*建立 socket 连接*/
   if ((sockfd = socket(AF_INET,SOCK_STREAM,0))== -1)
   {
     printf("socket error\n");
   }
   printf("Socket id = %d\n",sockfd);
   
   /*设置 sockaddr_in 结构体中相关参数*/
   server_sockaddr.sin_family = AF_INET;
   server_sockaddr.sin_port = htons(LISTEN_PORT);
   server_sockaddr.sin_addr.s_addr = INADDR_ANY;

   i=1;
   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
   /*绑定函数 bind()*/
   if (bind(sockfd, (struct sockaddr *)&server_sockaddr,
   sizeof(struct sockaddr)) == -1)
   {
     printf("Bind Error\n");
   }
   printf("Bind Success!\n");
   /*调用 listen()函数,创建未处理请求的队列*/
   if (listen(sockfd, MAX_QUE_CONN_NM) == -1)
   {
      printf("Listen Error\n");
   }
   printf("Listen...\n");


   /*调用 accept()函数,等待客户端的连接*/
   for(;;)
   {
       pthread_t threadNO;
       

       client_fd = accept(sockfd,(struct sockaddr *)&client_sockaddr, &sin_size);
       if (client_fd  == -1)
       {
          printf("Accept Error\n");
          break;
       }
       //创建客户端线程
       g_nClientNum++;
       printf("new clientID:%d,client num:%d\n",client_fd,g_nClientNum);
	   pthread_create(&threadNO, NULL, temp, (void*)client_fd);
	   pthread_create(&threadNO, NULL, wenshidu,(void*)client_fd); 

   }	
}
void * temp(void* arg)
{
	int sockfd= (int)arg;
	while(1)
	{
		char SBuff[255]={0};
		int nRecvLen = recv(sockfd,SBuff,254,0);

				if(nRecvLen<=0)
					{
						g_nClientNum--;
							printf("cleintID-%d closed,client num:%d\n",sockfd,g_nClientNum);
						break;
					}
		if(SBuff[0]=='s')
			
        {

		if(serialDataAvail(fd)>=1)
			{
			
						printf("缓冲池的字节数%d\n",serialDataAvail(fd));		
						read(fd,data,20);
						printf("%c%c%c%c%c%c%c%c%c%c",data[0],data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);
						printf("%c%c%c%c%c%c%c%c%c%c",data[10],data[11],data[12],data[13],data[14],data[15],data[16],data[17],data[18],data[19]);
						data[20]=(char)wen;
						data[21]=(char)shi;
						printf("%c%c",data[20],data[21]);
			            printf("wendu %dshidu %d",data[20],data[21]);		        
						send(sockfd,(char *)data,22,0);
				continue;
			}	
		}

		if(SBuff[0]=='c')
		{
			printf("receiver%c%c",SBuff[0],SBuff[1]);
			if(SBuff[1]=='a')
			{
				pthread_mutex_lock(&g_mutexCmd);
				if(s<=19)
				{
					s+=3;
					softPwmWrite(1,s);
				}
				pthread_mutex_unlock(&g_mutexCmd);
			}
			else if(SBuff[1]=='b')
			{
				pthread_mutex_lock(&g_mutexCmd);
				if(s==7)
				{
					softPwmWrite(1,5);
				}
				else
				{
					s-=3;
					softPwmWrite(1,s);
				}
				pthread_mutex_unlock(&g_mutexCmd);
			}
		}
		
		if(SBuff[0]=='L')
		{
			if(SBuff[1]=='E')
			{
				if(SBuff[2]=='D')
				{
					printf("receiver%c%c%c%c%c%c",SBuff[0],SBuff[1],SBuff[2],SBuff[3],SBuff[4],SBuff[5],SBuff[6]);
					printf("write %d",write(fd,(char*)(SBuff),6));
				}
			}
		}	
		if(SBuff[0]=='B'){
			if(SBuff[1]=='E')
			{
				if(SBuff[2]=='E'){
					if(SBuff[3]=='P'){
						if(SBuff[4]=='0'){
				printf("receiver%c%c%c%c%c%c ",SBuff[0],SBuff[1],SBuff[2],SBuff[3],SBuff[4],SBuff[5]);
		        printf("write  %d",write(fd,(char*)(SBuff),6));
						}	
						}	
					}
				}
			}
		}	
	}


