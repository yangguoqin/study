#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
//#define  PORT 1234
#define  QUEUE_LEN 10
#define CMD_PUT 2
typedef struct file_info_tag
{
    char opt;
    char name[256];
    int len;
}file_info_t;

typedef struct msg_tag
{
    int type;
    int len;
}msg_t;

int block_read(int fd,char *buf,int len)
{
    int read_size = 0;
    int n = 0;
    while(read_size < len)
    {
        n = read(fd, buf + read_size, len-read_size);
	if(n < 0)
	{
	    perror(strerror(errno));
	    break;
	}else if( 0 == n)
		{
	    perror(strerror(errno));
	    break;
	}
	read_size += n;
    }
    return 0;
}

int main(int argc, char **argv)
{
	if(3 != argc)
	{
	    printf("use ./server ip port!\n");
	    return 0;
	}
	// 1 create socket
        int listenfd = socket(PF_INET,SOCK_STREAM,0);
        int opt = SO_REUSEADDR; 
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	// 2 bind
	struct  sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family	= AF_INET;
	server.sin_port		= htons(atoi(argv[2]));
	server.sin_addr.s_addr	= inet_addr(argv[1]);
	int ret = bind(listenfd, (struct sockaddr *)&server, sizeof(server));
	if(ret < 0)
	{
	    perror(strerror(errno));
	    close(listenfd);
	}
	// 3 listen
	listen(listenfd, QUEUE_LEN);
	// 4 accept
	struct  sockaddr_in client;
	socklen_t addrlen = sizeof(client);
    while(1)
    {
	int connectfd = accept(listenfd, (struct sockaddr*)&client, &addrlen);
	if(connectfd < 0)
	{
	    perror(strerror(errno));
	    close(listenfd);
	    close(connectfd);
	    return 0;
	}
	// 5 recv data
        msg_t msg = {0};
	int num = read(connectfd, &msg, sizeof(msg));
	if(num != sizeof(msg))
	{
	    perror(strerror(errno));
	    close(listenfd);
	    close(connectfd);
	    return 0;
	}
    if(msg.type == CMD_PUT)
    {
	file_info_t buf = {0};
	num = read(connectfd, &buf, sizeof(buf));
	if(num != sizeof(buf))
	{
	    perror(strerror(errno));
	    close(connectfd);
	    close(listenfd);
	}
	// 6 exit handle;
	printf("rcvd %d\n", buf.opt);
	printf("rcvd %s\n", buf.name);
	printf("rcvd %d\n", buf.len);
	char *data;
	data = (char *)malloc(buf.len + 1);
	memset(data,0,buf.len +1 );
	block_read(connectfd, data , buf.len);
	int fd = open(buf.name,O_RDWR|O_CREAT,0644);
	write(fd ,data,buf.len );
	free(data);
	close(fd);
	close(connectfd);
        continue;
    }
    close(connectfd);
    close(listenfd);
    }	
    return 0;
}
