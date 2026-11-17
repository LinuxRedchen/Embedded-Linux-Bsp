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
    ssize_t rd;
    char buf[20];
    if(argc < 2)
    {
        printf("Usage : %s <File>",argv[1]);
        return -1;
    }

    fd = open(argv[1], O_RDONLY);

    if(fd < 0)
    {
        printf("can not open this file : %s\n",argv[1]);
        printf("error : %d\n",errno);
        printf("open : %s\n",strerror(errno));
        perror("open");
        return -1;
    }
    else
    {
        printf("fd = %d\n",fd);
    }

    rd = read(fd,buf,100);
    if(rd > 0)
    {
        buf[rd] = '\0';
        printf("读取到%zd字节:%s\r\n",rd,buf);
    }
    else
    {
        printf("error read!\r\n");
    }

    close(fd);

    return 0;
}
