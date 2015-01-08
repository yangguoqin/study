#include "../../include/include.h"

extern char name[100];              //定义此变量用以存放登录后的帐号
extern char name1[100];             //定义此变量用以存放登录后的用户 

void outlook(void);
void outlook1(void);
int block_write(int fd ,char *buf, int len);
int set_disp_mode(int fd,int option);
int getpasswd(char *passwd,int size);
extern char sql_create_student1[256];
//写线程 ，将用户命令写给服务器
void *thread_handle1(void *arg)
{ 
int err = 0;
int state = 0;
int no_state = 0;
    int m = 0;
    char password[100];
    int sockfd = *((int *)arg);
    while(1)
    {
        {
            if(0 == state)
            {
                sleep(1);
                err = 0;
                if(state == 1)
                {
                    break;
                }
                system("reset");
                outlook();
                printf("请输入您的命令:");
                char commder[10];
                scanf("%s",commder);
                
                //注册用户
                if(strcmp(commder,"reg") == 0)
                {
                    printf("请输入您注册的用户名:");
                    char name1[100];
                    memset(&password,0,100);
                    scanf("%s",name1);
                    getchar();
                    set_disp_mode(STDIN_FILENO,0);             //取消回显
                    getpasswd(password,sizeof(password));      //获取密码
                    char *p ;
                    p = password;
                    while(*p != '\n')
                    {
                        p++;
                    }
                    *p = '\0';                                     
                    
                    msg_t msg1 ;                               
                    strcpy(msg1.name,name1);
                    strcpy(msg1.password,password);
                    msg1.action = 1;
                    memset(msg1.toname,0,sizeof(100));
                    memset(msg1.msg,0,sizeof(100)); 
                    int num = write(sockfd, &msg1, sizeof(msg_t));
                    if(num != sizeof(msg_t))
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                    continue;
                }
                
                //登录用户
                if(strcmp(commder,"log") == 0)
                {
                    printf("请输入您登录的ID:");
                    memset(&name,0,100);
                    memset(&password,0,100);
                    scanf("%s",name);
                    getchar();
                    set_disp_mode(STDIN_FILENO,0);
                    getpasswd(password,sizeof(password));
                    char *p ;
                    p = password;
                    while(*p != '\n')
                    {
                        p++;
                    }
                    *p = '\0';
                    
                    msg_t msg1 ;
                    strcpy(msg1.account,name);
                    strcpy(msg1.password,password);
                    msg1.action = 2;
                    memset(msg1.toname,0,sizeof(100));
                    memset(msg1.msg ,0,sizeof(100));
                    int num = write(sockfd, &msg1, sizeof(msg_t));     //结构体写往服务器
                    if(num != sizeof(msg_t))
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                }

                if(strcmp(commder,"quit") == 0)
                {
                    msg_t msg1;
                    msg1.action = 7;
                    strcpy(msg1.account,name);                          //要退出的帐号 
                    int num = write(sockfd, &msg1, sizeof(msg_t));
                    if(num != sizeof(msg_t))
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                    close(sockfd);
                    return NULL;
                }
                
                else
                {
                    //printf("您的命令有误，请重新输入:\n");
                    err = 1;                                       //如果命令有误阻止state全局变量置1无法进入登录界面
                }
                sleep(1);
                
                if(err == 0)
                {
                    state = 1;
                } 
            }
            else 
            {
                sleep(2);
                
                if(m == 0)
                {
                    system("reset");
                    outlook1();
                    printf("\033[40;31m亲爱的%s\033[0m\n",name1);   //显示登录用户的用户名
                    m = 1;
                }
                
                printf("请输入您的命令:");
                char commder[10];
                scanf("%s",commder);
                
                if(strcmp(name,"100000000") == 0)                  //超级用户可以额外享有踢人禁言解禁等功能
                {
                    if(strcmp(commder,"kick") == 0)                //踢人操作处理
                    {
                        printf("请输入您要踢出的用户:");
                        msg_t msg1;
                        msg1.action = 10;
                        scanf("%s",msg1.toname);
                        int num = write(sockfd, &msg1, sizeof(msg_t));
                        if(num != sizeof(msg_t))
                        {
                            perror(strerror(errno));
                            close(sockfd);
                        }
                        continue;
                    }
                    
                    if(strcmp(commder,"stop") == 0)                //禁言
                    {
                        printf("请输入您要禁言的用户:");
                        msg_t msg1;
                        msg1.action = 11;
                        scanf("%s",msg1.toname);
                        int num = write(sockfd, &msg1, sizeof(msg_t));
                        if(num != sizeof(msg_t))
                        {
                            perror(strerror(errno));
                            close(sockfd);
                        }
                        continue;
                    }
                    
                    if(strcmp(commder,"unstop") == 0)
                    {
                        printf("请输入您要解禁的用户:");         //解禁
                        msg_t msg1;
                        msg1.action = 12;
                        scanf("%s",msg1.toname);
                        int num = write(sockfd, &msg1, sizeof(msg_t));
                        if(num != sizeof(msg_t))
                        {
                            perror(strerror(errno));
                            close(sockfd);
                        }
                        continue;
                    }
                }
                
                if(strcmp(commder,"show") == 0)                  //显示所有在线用户帐号和用户名
                {
                    msg_t msg1;
                    msg1.action = 3;
                    int num = write(sockfd, &msg1, sizeof(msg_t));
                    if(num != sizeof(msg_t))                        
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                    continue;
                }
                
                if(no_state == 0)                              //禁言全局变量，若为1，则无法发言
                {
                    if(strcmp(commder,"sto") == 0)             // 对某个帐号的用户私秘 
                    {
                        msg_t msg1;
                        msg1.action = 4;
                        printf("请输入您私密的帐户和内容:");
                        scanf("%s ",msg1.toname);
                        gets(msg1.msg);
                        if(strcmp(msg1.msg,"welcome") == 0)    //如果内容为welcome则替换为....  
                        {
                            memset(msg1.msg, 0, sizeof(100));
                            sprintf(msg1.msg,"%s大侠，欢迎你来到我们的聊天室!",msg1.toname);
                        }
                        strcpy(msg1.account,name);             //将登录中的帐号和用户名写过去
                        strcpy(msg1.name,name1);
                        int num = write(sockfd, &msg1, sizeof(msg_t));
                        if(num != sizeof(msg_t))
                        {
                            perror(strerror(errno));
                            close(sockfd);
                        }
                        continue;
                    }
                    
                    if(strcmp(commder,"sta") == 0)                   //对所有人说话
                    {
                        msg_t msg1;
                        msg1.action = 5;
                        printf("请输入您对大家说的话:");
                        getchar();
                        gets(msg1.msg);
                        if(strcmp(msg1.msg,"^_^") == 0)              //如果输入为笑脸则替换为嘿嘿
                        {
                            memset(msg1.msg, 0, sizeof(100));
                            sprintf(msg1.msg,"嘿嘿");
                        }
                        strcpy(msg1.account,name);
                        strcpy(msg1.name,name1);
                        int num = write(sockfd, &msg1, sizeof(msg_t));
                        if(num != sizeof(msg_t))
                        {
                            perror(strerror(errno));
                            close(sockfd);
                        }
                        continue;
                    }
                }
                
                if(strcmp(commder,"help") == 0)                     //help查看命令界面          
                {
                    system("reset");
                    outlook1();                                  
                    printf("\033[40;31m亲爱的%s\033[0m\n",name1);   
                    continue;
                }
                
                if(strcmp(commder,"repassword") == 0)               //修改密码命令        
                {
                    memset(&password,0,100);
                    printf("请输入新密码:");
                    getchar();
                    gets(password);
                    msg_t msg1 ;
                    strcpy(msg1.name,name);
                    strcpy(msg1.password,password);
                    msg1.action = 14;
                    int num = write(sockfd, &msg1, sizeof(msg_t));
                    if(num != sizeof(msg_t))
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                    continue;
                }

                if(strcmp(commder,"send") == 0)                     //发送文件命令
                {
                    msg_t msg1;
                    msg1.action = 9;
                    strcpy(msg1.name,name);
                    printf("请输入您发送文件的对象:");              //发送对象帐号 
                    scanf("%s",msg1.toname);
                    getchar();
                    printf("请输入您要发送的文件名:");
                    gets(msg1.msg);
                    
                    int fd = open(msg1.msg,O_RDWR|O_CREAT,0644);
                    int m = lseek(fd ,0 ,SEEK_END);                 //m为文件的总共大小
                    lseek(fd,0,SEEK_SET);
                    char *data = (char *)malloc(m + 1);
                    memset(data,0,m + 1);
                    int num = read(fd , data, m);                   //将文件内容读入data中 
                    msg1.len = m;
                    
                    num = write(sockfd, &msg1, sizeof(msg_t));      //将消息结构体传给服务器
                    close(fd);
                    
                    num = block_write(sockfd, data, m);             //将data即文件内容写过去
                    free(data);
                    continue;
                }

                if(strcmp(commder,"off") == 0)                      //离线操作，离线之后还可以登录
                {
                    msg_t msg1;
                    msg1.action = 8;
                    strcpy(msg1.name,name);
                    
                    int num = write(sockfd, &msg1, sizeof(msg_t));
                    if(num != sizeof(msg_t))
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                    state = 0;
                    continue;
                }

                if(strcmp(commder,"quit") == 0)                  //退出用户登录状态结束线程
                {
                    msg_t msg1;
                    msg1.action = 7;
                    strcpy(msg1.account,name);
                    int num = write(sockfd, &msg1, sizeof(msg_t));
                    if(num != sizeof(msg_t))
                    {
                        perror(strerror(errno));
                        close(sockfd);
                    }
                    close(sockfd);
                    return NULL;
                }
                
                else
                {
                                                                 //命令出错后重新等待用户输入命令
                    continue;
                }

            }
        }	
    }
    close(sockfd);
    return NULL;
}

