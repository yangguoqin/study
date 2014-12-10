#include<reg51.h>
#define OSC 11059200
#define BAUDRATE 9600

void main(main)
{
  unsigned char c;
  TMOD=0x20;                          %T1工作在方式2，作为波特率发生器
  SCON=0x50;                          %串口方式1（N81模式），REN=1（接收）
  PCON=0x80;                          %SMOD=1
  TL1=256-(OSC/12/16/BAUDRATE);       
  TH1=256-(OSC/12/16/BAUDRATE);       %设置定时器初始值
  TR1=1;                              %启动定时器，输出波特率时钟
  RI=0;
  TI=0;                               %确保程序开始时RI/TI标志无效
  whille(1)                           %主程序
  {
    while(RI==0);                     %首先等待对方发送数据
    RI=0;                             %能执行到这里,说明RI=1，接收数据有效
    c=SBUF;                           %将接收数据从SBUF读出至内部变量c中
    switch(c)                         %使用switch（）进行分支判断
    {
      case 0x0d：
      case 0x0a:SBUF=c;               %回车/换行原样送回
                break;
      default:  SBUF=++c;             %其余数据+1后送回
                break;
    }
    while(!TI);                       %等待串行帧发送完毕
    TI=0;                             %清零TI后开始下次循环
  }
}
      
