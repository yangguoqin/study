#include <reg51.h>
#include <stdio.h>
#include <intrins.h>
#define OSC 11059200
#define BAUDRATE 9600
sbit CLK=P1^0;
sbit DATA=P1^1;
sbit CS=P1^2;
unsigned int DAConvert(unsigned int da)
{
  int i;
  da<<=2;
  da&=0xFFC;
  SCK=1;
  CS=0;
  for(i=0;i<12;i++)
  {
  if(da & 0x800) DIN=1;
  else DIN=0;
  SCK=1;
  SCK=0;
  da<<=1;
  }
  CS=1;
  SCK=1;
  DIN=1;
}

void main(void)
{
  unsigned int i;
  TMOD=0x20;
  SCON=0x50;
  PCON|=0x80;
  TL1=256-(OSC/12/16/BAUDRATE);
  TH1=256-(OSC/12/16/BAUDRATE);
  TR1=1;
  TI=1;
  printf("\r\nTLC1549 test starting...");
  while(1)
  {
    for(i=0;i<1024;i+=32)
    {
	     aDAConvert(i);
    }
  }
}
