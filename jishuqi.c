#include<reg51.h>
unsigned char code CharCode[]={0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};

void main(void)
{
  unsigned char cc,count;
  TMOD=0x05;
  TH0=0;
  TL0=0;
  TR0=1;
  P1=CharCode[0];
  count=0;
  cc=TL0;
  while(1)
  {
    if(cc!=TL0)
    {
      cc=TL0;
      count++;
      if(count>=10) count=0;
      P1=CharCode[count];
    }
  }
}
