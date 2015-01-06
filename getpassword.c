#include "../../include/include.h"

int getpasswd(char *passwd,int size)
{
    int c;
    int n = 0;
    printf("请输入密码:");
    do
    {
        c = getchar();
        if((c != '\n')|(c != '\r'))
        {
            passwd[n++] = c;
        }
    }while(c != '\n' && c != '\r' && n < (size - 1));
    passwd[n] = '\0';
    return n;
}
