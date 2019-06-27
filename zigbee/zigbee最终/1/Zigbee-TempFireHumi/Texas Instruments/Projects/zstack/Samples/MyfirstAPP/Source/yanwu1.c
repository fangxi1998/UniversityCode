#include <ioCC2530.h>
#include <string.h>
#include "yanwu1.h"
#define uchar unsigned char
#define uint unsigned int
uchar _data[4];

void getyanwu(void)
{
  DATA_yanwu=1;
  P0DIR &= ~0x04; //重新配置 IO 口方向 输入
  if(DATA_yanwu)
  {
    _data[0]='0';
  }
  else
  {
    _data[0]='1';
  }
}
