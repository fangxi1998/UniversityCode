#include "LCD128_64.h"
#include "Font.h"
#include "hal_lcd.h"
#include "OSAL.h"
#include "string.h"

/****************************************************
* B) Command Table per device *
****************************************************/
#define 	DisplayOff 	0xAE
#define 	DisplayOn 	0xAF
#define 	DisplayStart 	0x40
#define 	PageAddr 	0xB0
#define 	ColAddrHi 	0x10
#define 	ColAddrLo 	0x00
#define 	SegRemapOff 	0xA0
#define 	SegRemapOn 	0xA1
#define 	NormalDisp 	0xA6
#define 	ReverseDisp 	0xA7
#define 	ExitEntireD 	0xA4
#define 	EntEntireD 	0xA5
#define 	EnterRMW 	0xE0
#define 	ExitRMW 	0xEE
#define 	SWRest 		0xE2
#define 	ComRemapOff 	0xC0
#define 	ComRemapOn 	0xC8
#define 	PwrCtrlReg 	0x28
#define 	OPampBuffer 	0x01
#define 	IntReg 		0x02
#define 	IntVolBstr 	0x04
#define 	IntRegRatio 	0x20
#define 	ContCtrlReg 	0x81
#define 	CmdMuxRatio 	0x48
#define 	CmdBiasRatio 	0x50
#define 	DispOffset 	0x44
#define 	IconModeOn 	0xA3
#define 	IconModeOff 	0xA2
#define 	NlineInver 	0x4C
#define 	DCDCconver 	0x64
#define 	PowersavStandby 0xA8
#define 	PowersavSleep 	0xA9
#define 	PowersavOff 	0xE1
#define 	InterOsc 	0xAB
#define 	Device SSD1821 			/* device under demo */
#define 	ColNo 		132 		/* number of Column/Seg on LCD glass*/
#define 	RowNo 		64		/* number of Row/Com/Mux */
#define 	PS 		1 		/* fixed to Parallel mode */
#define 	PageNo 		10 		/* Total no of RAM pages */
#define 	IconPage 	10 		/* Icon Page number */
#define 	All0 		6 		/* 3 for all 0, 4 for all 1 */
#define 	All1 		4
#define 	iIntRegValue 	1 		/*Internal Regulator Resistor Ratio Value */
#define 	iContCtrlRegValue 16 		/* Contrast Control Register Value */
#define 	iIntRegValuea 	20 		/*Internal Regulator Resistor Ratio Value */
#define 	iContCtrlRegValuea 16 		/* Contrast Control Register Value */
#define 	iIntRegValueb 	1 		/*Internal Regulator Resistor Ratio Value */
#define 	iContCtrlRegValueb 16 		/* Contrast Control Register Value */
#define 	MSGNo 		16
#define 	MSGLength 	22
#define 	SSLNameNo 	4
#define 	DevicePg 	0 		//RAM page for showing device name
#define 	FeaturePg 	1 		//RAM page for showing feature
#define 	GRAPHICNo 	13
#define 	xlogo 		38
#define 	ylogo 		5
#define 	xsolomon 	91
#define 	ysolomon 	2
#define 	xsystech 	81
#define 	ysystech 	2
#define 	xlimited 	70
#define 	ylimited 	2
#define 	xcc 		16
#define 	ycc 		2
#define 	xpageq 		128
#define 	ypageq 		4
#define 	horizonal 	0
#define 	d_time 		60
////////////////////////////////////////////////////////////////////////////////////////////
#define  CS   P1_6     //Ƭѡ�ź�
#define  SID  P1_5     //�����ź�
#define  SCLK P1_4     //ʱ���ź�


void Print8(uint16 y,uint16 x, uint8 ch[],uint16 yn);

uint8 ContrastValue =90;
void WriteLCD(uint8 fs, uint8 da);
void Write595(uint8 dat);
void delay_us(uint16 s);
void delay1(uint8 jj);
void contrastctrl(uint8 start, uint8 stop);
void HalLcdInit(void);
void PrintCh8(uint16 y,uint16 x, uint8 ch,uint16 yn);
void upLcd( char *ptr,uint8 op );
void HalLcdClearLine( uint8 line );
//****************�Լ��ӵ�********************************
void write_data(unsigned char Dispdata);
void write_com(unsigned char cmdcode);
void sendbyte(unsigned char zdata);
void delay(unsigned int t);
void print_LCDdata(char  *dsp);
void kaijijiemian(void);
void Test(void);
void Router_Join(unsigned char s);

int i=0;


void delay1(uint8 jj)
{
	uint8 i;
	for(i=0; i<jj; i++);
}





void delay_us(uint16 s)
{
	uint16 i;
	for(i=0; i<s; i++);
	for(i=0; i<s; i++);
        for(i=0; i<s; i++);
	for(i=0; i<s; i++);
}


//******************************************************************************
//��������void Write595(uint8 dat)
//���룺����
//�������
//����������595д���ݣ�һ��д��8λ
//******************************************************************************
void Write595(uint8 dat)
{
	
	uint8 ii;		
			
	for(ii = 0 ; ii < 8; ii++)
	{
		if(dat & 0x80) 	LCD_595_DAT = 1;
		else		LCD_595_DAT = 0;
		
		dat <<= 1;
		LCD_595_CK = 1;	
		LCD_595_CK = 0;
	}
	LCD_595_LD = 1;
	LCD_595_LD = 0;
}




//*****************************************************************************
//*****************************************************************************
//��������void delay(unsigned int n)
//������������ͨ͢ʱ����
//*****************************************************************************
void WriteLCD(uint8 fs, uint8 da)
{
	delay1(2);
	LCD_CS1 = 0;
	LCD_RW = 0;			//д����
	//delay1(0);	

	if(fs){
		LCD_RS = 1;	
	}
	else{
		LCD_RS = 0;
	}
       // delay1(0);

        Write595(da);
	LCD_E = 1;// = 1;
        delay1(2);
	LCD_E = 0;// = 0;					
	//delay1(0);
	LCD_CS1 = 1;
}
/*
//ԭ�������εĳ���
uint8 ReadLCD(uint8 fs)
{
	uint8 temp = 0;
	LCD_CS1 = 0;
	NOP;
	NOP;
	NOP;
	NOP;
	do{						
		LCD_RW = 1;
		LCD_RS = 0;
		LCD_E = 1;
		NOP;
		NOP;							
		temp = P1 & 0x80;			
		LCD_E = 0;			

	}while(temp != 0);	

	if(fs){
		LCD_RS = 1;	
	}
	else{
		LCD_RS = 0;
	}
	
	LCD_E = 1;
	NOP;	
	NOP;
	NOP;
	NOP;	
	temp = P1;	
	LCD_E = 0;	
	LCD_CS1 = 1;
	return(temp);
}


*/
void SetRamAddr(uint8 x ,uint8 y)
{
	uint8 temp;
	
	temp = 0x0f & x;
	WriteLCD(COMMAND , PageAddr|temp);

	temp = 0x0f & (y >> 4);
	WriteLCD(COMMAND , ColAddrHi|temp);
	temp = 0x0f & y;
	WriteLCD(COMMAND , ColAddrLo|temp);
}


/*******************************************************************************
//��������void SetContrast(uint8 Gain, uint8 Step)
//���ܣ�lcd�Աȶ��趨
//���룺Page-ҳ��Col-��
//�������
********************************************************************************/
void SetContrast(uint8 Gain, uint8 Step)
{
	WriteLCD(COMMAND , IntRegRatio | (0x0f & Gain)); 	//�趨�ڲ�����
	WriteLCD(COMMAND , ContCtrlReg); 			//�趨�ڲ��Աȿ�����
	WriteLCD(COMMAND , 0x3f & Step);
}



/*******************************************************************************
//��������void InitDisplay(void)
//���ܣ�lcd�趨Ϊ������ʾ״̬
//���룺��
//�������
********************************************************************************/
void InitDisplay(void)
{
	WriteLCD(COMMAND , DisplayOff);			//����ʾ
	WriteLCD(COMMAND , SegRemapOn);    			//ks0713/ssd1815
	WriteLCD(COMMAND , ComRemapOn);    			//ssd1815
	SetContrast(iIntRegValue, iContCtrlRegValue); 	//�趨ȱʡ�Աȶ�
	WriteLCD(COMMAND , PwrCtrlReg | IntVolBstr | IntReg | OPampBuffer); //turn on booster, regulator & divider
	WriteLCD(COMMAND , DisplayOn);				//����ʾ
}


/*******************************************************************************
//��������void contrastctrl(uint8 start,stop)
//���ܣ�lcd�Աȶȵ���
//���룺��
//�������
********************************************************************************/

void contrastctrl(uint8 start, uint8 stop)
{
	uint8 i;
	if (start < stop)
	{
		for (i=start; i<stop; i+=1)
		{
			SetContrast(iIntRegValue, i); //slowly turn on display
			delay_us(80);
		}
	}
	else
	{
		for (i=start; i>stop; i-=1)
		{
			SetContrast(iIntRegValue, i); //slowly turn off display
			delay_us(120);
		}
	}
}



//**********�Լ��������*****************************************
/*
void ClearScreen(void)
{
 	uint8 x,y;
	for(x = 0;x < 8 ;x++){
          SetRamAddr(x , 0);
	  	for(y = 0 ; y < 128 ; y++)
                {	  					
		     WriteLCD(DATA , 0x00);
		}		
	}
}
*/
//*********�Լ����ϵ�***********************
void ClearScreen(void)
{
   
  
        write_com(0x01);  //�ָ���ԭλ��
        delay(20);
        write_com(0x03);//����
	delay(200);delay(200);delay(200);
        delay(200);delay(200);delay(200);
}

//*******�Լ����ϵ� ************************************
void delay(unsigned int t)
{
	unsigned int i,j;
	for(i=t; i>0;  i--)
        for(j=541; j>0; j--);
}

/********************************************************************
* ���� : sendbyte()
* ���� : ����Һ���Ĵ���ͨ��Э�飬��������
* ���� : zdata
* ��� : ��
*��ע���Լ��ӵ�
***********************************************************************/

void sendbyte(unsigned char zdata)
{
	unsigned int i;
	for(i=0; i<8; i++)
	{
		if((zdata << i) & 0x80)
		{
			SID = 1;
		}
		else 
		{
			SID = 0;
		}
                asm("nop");asm("nop");
		SCLK = 0;
                asm("nop");asm("nop");
                asm("nop");asm("nop");
		SCLK = 1;
                asm("nop");asm("nop");
                asm("nop");asm("nop");
                SCLK = 0;
	}
}

/********************************************************************
* ���� : write_com()
* ���� : д����ָ��
* ���� : cmdcode
* ��� : ��
* ��ע :�Լ��ӵ�
***********************************************************************/

void write_com(unsigned char cmdcode)
{
	CS = 1;
	sendbyte(0xf8);
	sendbyte(cmdcode & 0xf0);
	sendbyte((cmdcode << 4) & 0xf0);
	delay(3);
        CS = 0;
}

/********************************************************************
* ���� : write_data()
* ���� : д�����ֽ�
* ���� : Dispdata
* ��� : ��
* ��ע :�Լ����ϵ�
*******************************************************************/
void write_data(unsigned char Dispdata)
{
	CS = 1;
        delay(100);
	sendbyte(0xfa);
        sendbyte(Dispdata & 0xf0);
	sendbyte((Dispdata << 4) & 0xf0);
	delay(2);
  
       /* CS = 1;
	sendbyte(0xfa);
	sendbyte(Dispdata & 0xf0);
	sendbyte((Dispdata << 4) & 0xf0);
	delay(3);
        CS = 0;*/
}
//*************�����ַ���**********************************
void print_LCDdata(char  *dsp)
{     
      char dispdata;
      CS = 1;
      sendbyte(0xfa);
      dispdata = *dsp;
      while(dispdata != '\0')
      {
          sendbyte(dispdata & 0xf0);
	  sendbyte((dispdata << 4) & 0xf0);
	  delay(2);
          dispdata = *(++dsp);
      } 
      CS = 0;
}



void HalLcdInit(void)
{	/*�Լ����εĳ����
        delay_us(10000);
        P1DIR |= 0xFC;
        P2DIR |= 0x01;
        P0DIR |= 0x02;
        P1_2 = 0;
	delay_us(100);	
	WriteLCD(COMMAND , 0xE2);//��λ

	delay_us(100);
	WriteLCD(COMMAND , 0xA3);

	delay_us(100);	
	WriteLCD(COMMAND , 0xA0);
	
	delay_us(100);
	WriteLCD(COMMAND , 0xC8);

	delay_us(100);	
	WriteLCD(COMMAND , 0x24);
	
	delay_us(100);
	WriteLCD(COMMAND , 0x81);

	delay_us(100);	
	WriteLCD(COMMAND , 0x14);
	
	delay_us(100);
	WriteLCD(COMMAND , 0x2F);

	delay_us(100);	
	WriteLCD(COMMAND , 0x40);//�ӵ�һ�п�ʼ��ʾ
	
	delay_us(100);
	WriteLCD(COMMAND , 0xB0);

	delay_us(100);	
	WriteLCD(COMMAND , 0x10);
	
	delay_us(100);
	WriteLCD(COMMAND , 0x00);

	delay_us(100);	
	WriteLCD(COMMAND , 0xAF);

	WriteLCD(COMMAND , 0x81);
	WriteLCD(COMMAND , 0x1b);
        delay_us(100);	
        SetContrast(iIntRegValuea,ContrastValue);
	ClearScreen();  */
       // HalLcdWriteString("IEEE:",1);
       // HalLcdWriteString("Init lcd",2);
      // HalLcdWriteString("Init lcd",3);
      //  PrintCh8(30,30,'O',1);
  //�Լ��ӵĳ���
       P1DIR |= (1 << 4)|(1 << 5)|(1 << 6);
       delay(100);
	write_com(0x30);
	delay(5);
	write_com(0x0c);
	delay(5);
        write_com(0x01);
        delay(50);
        write_com(0x03);
	delay(10);
  
}



/*******************************************************************************
//��������void Print6(uint8 xx, uint8 yy, uint8 ch1[], uint8 yn)
//���ܣ���ʾ6*8�ַ���
//���룺xx ,yy ����,ch1����ʾ���ַ���,yn�Ƿ񷴺�
//�������
********************************************************************************/

void Print6(uint8 xx, uint8 yy, uint8 ch1[], uint8 yn)		
{
	uint8 ii = 0;
	uint8 bb = 0;
	unsigned int index = 0 ;	
			
	while(ch1[bb] != '\0')
	{
                index = (unsigned int)(ch1[bb] - 0x20);
		index = (unsigned int)index*6;		
		for(ii=0;ii<6;ii++)
		{
			SetRamAddr(xx , yy);
			if(yn == 0)
			{
				WriteLCD(DATA, ~FontSystem6x8[index]);
				
			}
			else
			{
				WriteLCD(DATA, FontSystem6x8[index]);
			}		
			index += 1;
			yy += 1;
		}		
		bb += 1;
	}
}


//*******************************************************************************
//��������void Printn8(uint8 xx ,uint8 yy , uint32 no,uint8 yn,uint8 le)
//���ܣ���ʾ8*8һ���޷�������
//���룺xx , yy��Ļ����λ��,no����ʾ���� yn=0������ʾ yn=1������ʾ  le��Чλ
//�������
//*******************************************************************************
void Printn8(uint8 xx ,uint8 yy , uint32 no,uint8 yn,uint8 le)
{
	uint8 ch2[6];
	uint8 ii;

	for(ii = 1 ; ii <= le ;){
		ch2[le - ii] = no % 10 + 0x30;
		no /= 10;
		ii += 1;
	}
	ch2[le] = '\0';
	Print8(xx ,yy ,ch2 ,yn);
}

/*******************************************************************************
//��������void Print8(uint16 y,uint16 x, uint8 ch,uint16 yn)
//���ܣ���ʾ8*8�ַ�
//���룺xx ,yy ����,ch����ʾ���ַ�,yn�Ƿ񷴺�
//�������
********************************************************************************/
void PrintCh8(uint16 y,uint16 x, uint8 ch,uint16 yn)
{
	uint8 wm;
	uint16 adder;
	
	adder = (ch - 0x20) * 16;
	for(wm = 0;wm < 8;wm++)
	{
		SetRamAddr(y , x);
		if(yn == 0)
		{
			WriteLCD(DATA, ~Font8X8[adder]);
		}
		else
		{
			WriteLCD(DATA, Font8X8[adder]);
		}
		adder += 1;
		x += 1;
	}
	y += 1;
	x -= 8;
	for(wm = 0;wm < 8;wm++)
	{
		SetRamAddr(y , x);
		if(yn == 0)
		{
				WriteLCD(DATA, ~Font8X8[adder]);
		}
		else
		{
			WriteLCD(DATA, Font8X8[adder]);	
		}
		adder += 1;
		x += 1;
	}
}


/*******************************************************************************
//��������void Print8(uint16 y,uint16 x, uint8 ch[],uint16 yn)
//���ܣ���ʾ8*8�ַ���
//���룺xx ,yy ����,ch1����ʾ���ַ���,yn�Ƿ񷴺�
//�������
********************************************************************************/
void Print8(uint16 y,uint16 x, uint8 ch[],uint16 yn)
{
	uint8 wm ,ii = 0;
	uint16 adder;

	while(ch[ii] != '\0')
	{
		adder = (ch[ii] - 0x20) * 16;

		for(wm = 0;wm < 8;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, ~Font8X8[adder]);
			}
			else
			{
				WriteLCD(DATA, Font8X8[adder]);
			}
			adder += 1;
			x += 1;
		}
		y += 1;
		x -= 8;
		for(wm = 0;wm < 8;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, ~Font8X8[adder]);
			}
			else
			{
				WriteLCD(DATA, Font8X8[adder]);	
			}
			adder += 1;
			x += 1;
		}
		ii += 1;
		y -= 1;
	}

}


/*******************************************************************************
//��������void Print16(uint16 y,uint16 x,uint8 ch[],uint16 yn)
//���ܣ�����Ļ����ʾ����
//���룺x ,y ����,ch[]����ʾ�ĺ���,yn�Ƿ񷴺�
//�������
********************************************************************************
void Print16(uint16 y,uint16 x,uint8 ch[],uint16 yn)
{
	uint8 wm ,ii = 0;
	uint16 adder;

	wm = 0;
	adder = 1;
	while(FontNew8X16_Index[wm] > 128)
	{
		if(FontNew8X16_Index[wm] == ch[ii])
		{
			if(FontNew8X16_Index[wm + 1] == ch[ii + 1])
			{
				adder = wm * 14;
				break;
			}
		}
		wm += 2;				//�ҵ������������е�λ��
	}
	SetRamAddr(y , x);

	if(adder != 1)					//�ҵ����֣���ʾ����	
	{
		
		for(wm = 0;wm < 14;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, ~FontNew16X16[adder]);
			}
			else
			{
				WriteLCD(DATA, FontNew16X16[adder]);
			}
			adder += 1;
			x += 1;
		}
                for(wm = 0;wm < 2;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, 0xff);
			}
			else
			{
				WriteLCD(DATA, 0x00);
			}
			x += 1;
		}
		y += 1;
		x -=16;

		for(wm = 0;wm < 14;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, ~FontNew16X16[adder]);
			}
			else
			{
				WriteLCD(DATA, FontNew16X16[adder]);
			}
			adder += 1;
			x += 1;
		}
                for(wm = 0;wm < 2;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, 0xff);
			}
			else
			{
				WriteLCD(DATA, 0x00);
			}
			x += 1;
		}


	}
	else						//�Ҳ�������ʾ�ո�			
	{
		ii += 1;

		for(wm = 0;wm < 16;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, 0xff);
			}
			else
			{
				WriteLCD(DATA, 0x00);
			}
			x += 1;
		}
		y += 1;
		x -= 16;
		for(wm = 0;wm < 16;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, 0xff);
			}
			else
			{
				WriteLCD(DATA, 0x00);
			}
			x += 1;
		}
	}
}*/


/*******************************************************************************
//��������void Print(uint8 y, uint8 x, uint8 ch[], uint16 yn)
//���ܣ�ʵ�ֺ��ּ���ĸ�����ʾ
//���룺x ,y ����,ch[]����ʾ�ĺ��ֻ���ĸ,yn�Ƿ񷴺�
//�������
********************************************************************************/
void Print(uint8 y, uint8 x, uint8 ch[], uint16 yn)
{
	uint8 ch2[3];
	uint8 ii;
        ii = 0;
	while(ch[ii] != '\0')
	{
		if(ch[ii] > 128)
		{
			ch2[0] = ch[ii];
	 		ch2[1] = ch[ii + 1];
			ch2[2] = '\0';			//����Ϊ�����ֽ�
			//Print16(y , x , ch2 , yn);	//��ʾ����
			x += 16;
			ii += 2;
		}
		else
		{
			ch2[0] = ch[ii];	
			ch2[1] = '\0';			//��ĸռһ���ֽ�
			Print8(y , x , ch2 , yn);	//��ʾ��ĸ
			x += 8;
			ii += 1;
		}
	}
}
void HalLcdClearLine( uint8 line )
{
  Print8(line,0,"                ",1);
}
void HalLcdWriteString ( char *str, uint8 option)
{
  unsigned char i; 
  uint8 LcdBuf[20];
  osal_memcpy(LcdBuf,str,20);
  i = strlen(str);
  LcdBuf[i] = '\0';  
  switch (option)
  {
    case 1:
    case 2:
    case 3:      
    case 4:     
    case 5:    
    case 6:
       HalLcdClearLine( option%7 );
       Print8(option%7,0,(unsigned char *)LcdBuf,1);
     /*  y = option%7;
       x = 0;
	while(LcdBuf[ii] != '\0')
	{
		adder = (LcdBuf[ii] - 0x20) * 16;

		for(wm = 0;wm < 8;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, ~Font8X8[adder]);
			}
			else
			{
				WriteLCD(DATA, Font8X8[adder]);
			}
			adder += 1;
			x += 1;
		}
		y += 1;
		x -= 8;
		for(wm = 0;wm < 8;wm++)
		{
			SetRamAddr(y , x);
			if(yn == 0)
			{
				WriteLCD(DATA, ~Font8X8[adder]);
			}
			else
			{
				WriteLCD(DATA, Font8X8[adder]);	
			}
			adder += 1;
			x += 1;
		}
		ii += 1;
		y -= 1;
	}*/
      //Print8(option%7,0,(unsigned char *)LcdBuf,1);
      break;
    default :
      break;
  }
}

void HalLcdWriteValue ( uint32 value, const uint8 radix, uint8 option)
{
;
}

void HalLcdWriteScreen( char *line1, char *line2 )
{
#if (HAL_LCD == TRUE)
  HalLcdWriteString( line1, 3 );
  HalLcdWriteString( line2, 5 );
#endif

}
void HalLcdWriteStringValue( char *title, uint16 value, uint8 format, uint8 line )
{
;
}
void HalLcdWriteStringValueValue( char *title, uint16 value1, uint8 format1,
                                  uint16 value2, uint8 format2, uint8 line )
{
;
}
void upLcd( char *ptr,uint8 op )
{
  HalLcdWriteString(ptr,op);
}

void kaijijiemian(void)
{

     // P1DIR &= (0 << 0)|(0 << 1)|(0 << 2)|(0 << 3);
      delay(10);
      HalLcdInit();
      delay(100);
	 
                    delay(200); delay(200);
		    Test(); 
                    delay(20);
              
                
                
}

void Test(void)
{
      
           write_com(0x80);
           print_LCDdata("������  ");
	//write_com(0x92);
	//write_data("��ϢѧԺ");
	write_com(0x91);
	print_LCDdata("���罨���ɹ�");
	write_com(0x88);
	print_LCDdata("SHORTADDR:0x0000");
}

void Router_Join(unsigned char s)
{        
  
        ClearScreen();
        write_com(0x80);
        print_LCDdata("������   ");
	//write_com(0x92);
	//write_data(" ��ϢѧԺ");
	write_com(0x91);
	print_LCDdata("Router");
        write_com(0x95);
        write_data(s);
	write_com(0x89);
	print_LCDdata("JoinSuccess");
     
}


