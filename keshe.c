#include<reg51.h>
#include <stdio.h>
#include <intrins.h>
#define OSC  11059200
#define BAUDTATE 9600
#define uchar unsigned char
sbit CLK=P1^0;
sbit DATA=P1^1;
sbit CS=P1^2;
sbit RS=P1^7;
sbit RW=P1^6;
sbit E=P1^5;
sbit K=P0^0;
uchar disbuffer[5]={0,'.',0,0,'V'};
void init(void);
void wc51r(uchar i);
void wc51ddr(uchar i);
void fbusy(void);
void disp(void);

void Delay1ms(int ms)
{
int i;
while(ms--)
for(i=0;i<100;i++);
}
unsigned int ADConvert(void)
{
  int i;
  unsigned int ad;
  ad=0;
  DATA=1;
  CS=0;
  for(i=0;i<10;i++)
  {
    ad<<=1;
    CLK=0;
    _nop_();
    _nop_();
    _nop_();
    CLK=1;
    if(DATA)
    ad|=0x01;
    else ad&=0xFFFE;
  }
  CS=1;
  return ad;
}

void main()
{
   unsigned int i,j,k,ad;
   float adf;
   SP=0x50;
   init();
   disp();
   while(1)
  {
     if(K==0)
	 
	 
	 {

     for(j=0;j<10;j++)
     for(i=0;i<10000;i++);
     ad=ADConvert();
     ad=ADConvert();
     adf=(ad*5.0)/1024.0;
     adf=adf*100;
     disbuffer[0]=(int)adf/100+0x30;
     disbuffer[2]=(int)adf%100/10+0x30;
     disbuffer[3]=(int)adf%10+0x30;
     init();
     wc51r(0xc4);
     for(k=0;k<5;k++)
     wc51ddr(disbuffer[k]);
	 }
	 else 
	 {
	    init();
        disp();
        Delay1ms(100);
	 }

   }
}

void disp(void)
{
   wc51r(0x81);
   wc51ddr('2');
   wc51ddr('0');
   wc51ddr('8');
   wc51ddr('1');
   wc51ddr('2');
   wc51ddr('1');
   wc51ddr('2');
   wc51ddr('1');
   wc51ddr('5');
   wc51ddr(' ');
   wc51ddr('Y');
   wc51ddr('G');
   wc51ddr('Q');

}
void init()
{
   wc51r(0x01);
   wc51r(0x38);
   wc51r(0x0c);
   wc51r(0x06);
}
void fbusy()
{
   P2=0xff;RS=0;RW=1;
   E=0;E=1;
   while (P2&0x80)
   {E=0;E=1;}

}
void wc51r(uchar j)
{
   fbusy();
   E=0;RS=0;RW=0;
   E=1;
   P2=j;
   E=0;

}
void wc51ddr(uchar j)
{
   fbusy();
   E=0;RS=1;RW=0;
   E=1;
   P2=j;
   E=0;
}
