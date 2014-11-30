/*************************************************
  Copyright (C), 1994-2014, yangguoqin
  File name:      see
  Author:    yangguoqin   Version: 1.0       Date: 2014.11.30
  Description:    该程序查看停车场情况
  Others:         无
  Function List:  
                  see
		  查看停车场情况
  History:        no
*************************************************/

#include <stdio.h>
#include "../../include/typedef.h"

/*************************************************
  Function:       see
  Description:    查看停车场清况
  Calls:          conut_wait_queue time 
                  localtime  interface
  Called By:      choose
  Input:          park_stack,temp_stack,wait_queue
  Output:         no
  Return:         no
  Others:         no
*************************************************/

void see(Stack *park_stack, Stack *temp_stack, Link_queue *wait_queue)
{
    int i;
    int j;
    int count;
    int pop_num;
    
    j = park_stack->top;
    count = count_wait_queue(wait_queue);   //遍历等待队列

    printf("\t\033[40;36m当前停车场的情况:\033[0m\n\n");
    printf("\t\033[40;36m停车场一共有\033[0m\033[40;31m10\033[0m\033[40;36m个车位,当前已使用\033[0m\033[40;31m%d\033[0m\033[40;36m个车位，等待区有\033[0m\033[40;31m%d\033[0m\033[40;36m辆车在等候停车。\033[0m\033[0m\n\n",(park_stack->top) + 1,count);
    
    printf("\t\033[40;36m+------------------------------------+\n\033[0m");
    printf("\t\033[40;36m|车位号    |车牌号    | 停车时长(秒) |\n\033[0m");
    for(i = park_stack->top + 1; i > 0; i--)
    {
            double stop_time;

	    struct tm *park_time;
	    struct tm *now_time;
	    time_t pre_time;
	    time_t this_time;
	    
	    pre_time = park_stack->i_time[j--];
	    park_time = localtime(&pre_time);                //取出时间
	    pop_num = pop_park_stack(park_stack,i);   //取栈值

	    printf("\t\033[40;36m|------------------------------------|\n\033[0m");
	    printf("\t\033[40;36m|\033[0m\033[40;31m%-10d\033[0m\033[40;36m|\033[0m\033[40;31m%-10ld\033[0m",i,pop_num);
	    
	    time(&this_time);
	    now_time = localtime(&this_time);
	    stop_time = difftime(this_time,pre_time);
	    printf("\033[40;36m|\033[0m\033[40;31m%-14.0lf\033[0m\033[40;36m|\033[0m\n",stop_time);
	
    }

    printf("\t\033[40;36m+------------------------------------+\033[0m\n\n");
    printf("\t\033[40;36m请输入任意键回主菜单: \033[0m");
    scanf("%d",&i);
    system("reset");
    interface(park_stack,temp_stack,wait_queue);   //返回主界面

}
