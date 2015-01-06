#include "../../include/include.h"

int block_write(int fd ,char *buf, int len)
{
    int write_size = 0;
    int n = 0;
    while(write_size < len)
    {
        n = write(fd, buf + write_size,len - write_size);
        if(n < 0)
        {
            perror(strerror(errno));
            break;
        }else if ( 0 == n)
        {
            perror(strerror(errno));
            break;
        }
        write_size += n;
    }
    return 0;
}
