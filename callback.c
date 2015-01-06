#include "../../include/include.h"

extern char sql_create_student1[256];
int callback(void *not_used, int argc, char **argv, char **col_name)
{
    int i= 0;
    int count = 0;
    for(i = 0; i < argc; i++)
    {
        count = strlen(sql_create_student1);       
        sprintf(sql_create_student1 + count,"%s\t",argv[i]?argv[i]:"NULL");
    }
    printf("\n");
    return 0;
}
