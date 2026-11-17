#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>



int main(int argc,char **argv)
{
    int fd;
    fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC,0777);

    if(argc != 2)
    {
        printf("Usage : %s <File>\n",argv[0]);
        return -1;
    }

    if(fd < 0)
    {
        printf("can not open this file : %s\n",argv[1]);
        printf("error : %d\n",errno);
        printf("open : %s\n",strerror(errno));
        perror("errno");
    }

    close(fd);

    return 0;
}

