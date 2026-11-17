#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>


int main(int argc,char **argv)
{

    int fd;

    if(argc < 3)
    {
        printf("Usage : %s <File> <str1> <str2> ... ",argv[1]);
        return -1;
    }

    fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC,0666);

    if(fd < 0)
    {
        printf("can not open this file : %s\n",argv[1]);
        printf("error : %d\n",errno);
        printf("open : %s\n",strerror(errno));
        perror("open");
    }
    else
    {
        printf("fd = %d\n",fd);
    }

    for(int i = 2;i < argc ; i++)
    {
        int len = write(fd ,argv[i], strlen(argv[i]));

        if(len != strlen(argv[i]))
        {
            perror("write");
            break;
        }
        write(fd ,"\r\n", 2);

    }
    

    close(fd);

    return 0;
}
