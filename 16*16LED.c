#include<reg51.h>
unsigned char code ZmCode[]={///*婷 C3647*/0x01,0x04,0x02,0x0C,0x7F,0xE4,0x00,0x04,0x1F,0x9F,0x10,0x94,0x1F,0x94,0x00,0x12,0x7F,0xD2,0x20,0x2E,0x1F,0x88,0x04,0x14,0x04,0x24,0x04,0x22,0x07,0x01,0x02,0x00};
                                         //定义汉字字模
void LEDDelay(int ms)

{
  int i;
  while(ms--)
    for(i=0;i<140;i++);     //调整for循环控制变量大小可还变延时时长
}

void main(void)
{
  int i,j;
  unsigned char pos;
  
  j=0;
  pos=0x01;
  
  while(1)
  {
    pos=0x01;     //初始状态，显示第一行
    j=0;
    
    for(i=0;i<16;i++)   //共有16行，依次显示
    {
      if(pos==0) pos=0x01;
      
      P1=ZmCode[j++];    //读取一行汉字点阵数据（2字节，16位）
      P2=ZmCode[j++];
      
      if(i<8）     //显示上半部分
      {
        P0=~pos;
        P3=0xff;
      }
      else    //显示下半部分
      {
        P0=0xff;
        P3=~pos;
      }
      pos<<=1;
      LEDDelay(2);
    }
  }
}
