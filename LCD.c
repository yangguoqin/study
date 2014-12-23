#include<reg51.h>
#define uchar unsigned char
sbit RS=P1^7;
sbit RW=P1^6;
sbit E=P1^5;
void init(void);
void wc51r(uchar i);
void wc51ddr(uchar i);
void fbusy(void);
void disp(void);
//主函数
void main()
{
   
   SP=0x50;
   init();
   disp();
   while(1)	;
}

void disp(void)
{
   wc51r(0x84);    //写入显示缓冲区起始地址为第0行第4列
   wc51ddr('2');   //第0行第4列显示2
   wc51ddr('0');   //第0行第5列显示0
   wc51ddr('8');   //第0行第6列显示8
   wc51ddr('1');   //第0行第7列显示1
   wc51ddr('2');   //第0行第8列显示2
   wc51ddr('1');   //第0行第9列显示1
   wc51ddr('2');   //第0行第10列显示2
   wc51ddr('1');   //第0行第11列显示1
   wc51ddr('5');   //第0行第12列显示6
   wc51r(0xc4);    //写入显示缓冲区起始地址为第1行第4列
   wc51ddr('Y');
   wc51ddr('a');
   wc51ddr('n');
   wc51ddr('g');
   wc51ddr('g');
   wc51ddr('u');
   wc51ddr('o');
   wc51ddr('q');
   wc51ddr('i');
   wc51ddr('n');
}
//初始化函数
void init()
{
   wc51r(0x01);
   wc51r(0x38);
   wc51r(0x0c);
   wc51r(0x06);
}
//检查忙函数
void fbusy()
{
   P2=0xff;RS=0;RW=1;
   E=0;E=1;
   while (P2&0x80)
   {E=0;E=1;}

}
//写命令函数
void wc51r(uchar j)
{
   fbusy();
   E=0;RS=0;RW=0;
   E=1;
   P2=j;
   E=0;

}
//写数据函数
void wc51ddr(uchar j)
{
   fbusy();
   E=0;RS=1;RW=0;
   E=1;
   P2=j;
   E=0;
}
