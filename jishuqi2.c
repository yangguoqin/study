#include<reg51.h>
unsigned char code CharCode[]={0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
void main(void)
{
  EA=1;
  IT0=0;
  EX0=1;
  count=0;
  P1=CharCode[0];
  while(1);
}

void int_0(void) inerrupt0
{
  Delay 1ms (200);
  count++;
  if(count>=10)
  {
    count=0;
  }
  P1=CharCode[count];
  
  int i;
  while(ms--)
  for(i=0;i<100;i++);
}
