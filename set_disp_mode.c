#include "../../include/include.h"

int set_disp_mode(int fd,int option)
{
    int err;
    struct termios term;
    if(tcgetattr(fd,&term) == -1)
    {
        perror("Cannot get the attribution of the terminal");
        return 1;
    }
    if(option)
    {
        term.c_lflag|=ECHOFLAGS;
    }
    else
    {
        term.c_lflag &= ~ECHOFLAGS;
    }
    err = tcsetattr(fd,TCSAFLUSH,&term);
    if(err == -1 && err == EINTR)
    {
        perror("Cannot set the attribution of the terminal");
        return 1;
    }
    return 0;
}

