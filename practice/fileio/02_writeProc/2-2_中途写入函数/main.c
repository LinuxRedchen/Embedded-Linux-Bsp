#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define READ_BUF 1024

int main(int argc,char **argv)
{
    int fd;
    char tempbuf[READ_BUF];
    off_t pos;
    ssize_t rd;

    // 至少4个参数：程序名 文件名 偏移 待插入字符串
    if(argc < 4)
    {
        printf("Usage : %s <File> <offset> <str>\n", argv[0]);
        return -1;
    }

    pos = atoll(argv[2]);

    // 重点：删掉 O_TRUNC！！
    fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    if(fd < 0)
    {
        printf("can not open this file : %s\n",argv[1]);
        printf("error : %d\n",errno);
        printf("open : %s\n",strerror(errno));
        perror("open");
        return -1;
    }
    printf("fd = %d\n",fd);

    int tfd = open(".tempfile",O_RDWR | O_CREAT | O_TRUNC,0666);
    if(tfd < 0)
    {
        perror("tempfile open");
        close(fd);
        return -1;
    }

    // 跳到插入位置，读取后面数据存入临时文件
    if(lseek(fd, pos, SEEK_SET) == (off_t)-1)
    {
        perror("lseek");
        close(fd);
        close(tfd);
        return -1;
    }

    while((rd = read(fd, tempbuf, READ_BUF)) > 0)
    {
        if(write(tfd, tempbuf, (size_t)rd) != rd)
        {
            perror("write temp");
            close(fd);
            close(tfd);
            unlink(".tempfile");
            return -1;
        }
    }
    if(rd < 0)
    {
        perror("read file");
        close(fd);
        close(tfd);
        unlink(".tempfile");
        return -1;
    }

    // 回到插入点，写入新字符串
    if(lseek(fd, pos, SEEK_SET) == (off_t)-1)
    {
        perror("lseek back");
        close(fd);
        close(tfd);
        unlink(".tempfile");
        return -1;
    }
    const char *ins_str = argv[3];
    size_t slen = strlen(ins_str);
    if(write(fd, ins_str, slen) != (ssize_t)slen)
    {
        perror("write insert str");
        close(fd);
        close(tfd);
        unlink(".tempfile");
        return -1;
    }

    // 把临时文件的数据写回去
    if(lseek(tfd, 0, SEEK_SET) == (off_t)-1)
    {
        perror("lseek tfd");
        close(fd);
        close(tfd);
        unlink(".tempfile");
        return -1;
    }
    while((rd = read(tfd, tempbuf, READ_BUF)) > 0)
    {
        if(write(fd, tempbuf, (size_t)rd) != rd)
        {
            perror("write back");
            close(fd);
            close(tfd);
            unlink(".tempfile");
            return -1;
        }
    }
    if(rd < 0)
    {
        perror("read temp");
        close(fd);
        close(tfd);
        unlink(".tempfile");
        return -1;
    }

    close(tfd);
    close(fd);
    unlink(".tempfile");
    printf("Insert success at offset %lld\n", (long long)pos);

    return 0;
}
