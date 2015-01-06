#include "../../include/include.h"

int block_read(int fd ,char *buf, int len)
{
    int read_size = 0;
    int n = 0;
    while(read_size < len)
    {
        n = read(fd, buf + read_size,len - read_size);
        if(n < 0)
        {
            perror(strerror(errno));
            break;
        }else if ( 0 == n)
        {
            perror(strerror(errno));
            break;
        }
        read_size += n;
    }
    return 0;
}

