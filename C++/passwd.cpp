#include <stdio.h>
#include <string.h>

int main(int argc, char * argv[])
{
    int flag = 0;

    char buf[10];
    memset(buf, 0, sizeof(buf));
    strcpy(buf, argv[1]);
    
    if(0 == strcmp("pass", buf))
    {
        flag = 1;
    }

    if(flag)
    {
        printf("pass");
    }
    else
    {
        printf("fail");
    }

}
