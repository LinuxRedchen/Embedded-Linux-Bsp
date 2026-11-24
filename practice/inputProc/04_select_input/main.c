#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>


int fd;
struct input_id dev_ID;
int err;
unsigned char keybit[KEY_MAX/8 + 1];
int len;
int i,bit;
unsigned char byte;
int keycont;
static const char *key_names[] = {
    "KEY_RESERVED",
    "KEY_ESC",
    "KEY_1", 
    "KEY_2", 
    "KEY_3",
    "KEY_4", 
    "KEY_5", 
    "KEY_6",
    "KEY_7", 
    "KEY_8", 
    "KEY_9", 
    "KEY_0", 
    "KEY_MINUS", 
    "KEY_EQUAL", 
    "KEY_BACKSPACE", 
    "KEY_TAB",
    "KEY_Q", 
    "KEY_W", 
    "KEY_E", 
    "KEY_R", 
    "KEY_T", 
    "KEY_Y", 
    "KEY_U", 
    "KEY_I",
    "KEY_O", 
    "KEY_P", 
    "KEY_LEFTBRACE", 
    "KEY_RIGHTBRACE", 
    "KEY_ENTER", 
    "KEY_LEFTCTRL", 
    "KEY_A", 
    "KEY_S",
    "KEY_D", 
    "KEY_F", 
    "KEY_G", 
    "KEY_H", 
    "KEY_J", 
    "KEY_K", 
    "KEY_L", 
    "KEY_SEMICOLON",
    "KEY_APOSTROPHE", 
    "KEY_GRAVE", 
    "KEY_LEFTSHIFT", 
    "KEY_BACKSLASH", 
    "KEY_Z", 
    "KEY_X", 
    "KEY_C", 
    "KEY_V",
    "KEY_B", 
    "KEY_N", 
    "KEY_M", 
    "KEY_COMMA", 
    "KEY_DOT", 
    "KEY_SLASH", 
    "KEY_RIGHTSHIFT", 
    "KEY_KPASTERISK",
    "KEY_LEFTALT", 
    "KEY_SPACE", 
    "KEY_CAPSLOCK"
};
ssize_t ret;
struct input_event ev;

void print_devId(int tfd)
{
    err = ioctl(tfd,EVIOCGID, &dev_ID);
    if(err < 0)
    {
        perror("ioctl");
        close(tfd);
        return;
    }
    printf("bustype : 0x%x\r\n",dev_ID.bustype);
    printf("vendor  : 0x%x\r\n",dev_ID.vendor);
    printf("product : 0x%x\r\n",dev_ID.product);
    printf("version : 0x%x\r\n",dev_ID.version);
}

void print_key_support(int tfd)
{
    memset(keybit,0,sizeof(keybit));
    len = ioctl(tfd,EVIOCGBIT(EV_KEY,sizeof(keybit)),keybit);
    if(len > 0 && len <= sizeof(keybit))
    {
        for(i=0;i<len;i++)
        {
            byte = keybit[i];
            for(bit=0;bit<8;bit++)
            {
                if(byte & (1 << bit))
                {
                    keycont = i*8 + bit;
                    if(keycont < (int)(sizeof(key_names)/sizeof(char*)))
                    {
                        printf("%s  ",key_names[keycont]);
                    }
                    else
                    {
                        printf("KEY(%d)  ",keycont);
                    }
                }
            }
        }
        printf("\r\n");
    }
}

int main(int argc,char **argv)
{
    if(argc != 2)
    {
        printf("Usage : %s <dev>\r\n",argv[0]);
        return 0;
    }

    fd = open(argv[1], O_RDONLY | O_NONBLOCK);

    if(fd < 0)
    {
        perror("open");
    }

    print_devId(fd);

    print_key_support(fd);

    printf("查询模式 : select超时查询\r\n");

    while (1)
    {
        fd_set rfds;
        struct timeval tv;

        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        tv.tv_sec = 3;
        tv.tv_usec = 0;


        ret = select(fd + 1,&rfds, NULL, NULL, &tv);
        if(ret < 0)
        {
            perror("select");
            close(fd);
        }
        else if(ret == 0)
        {
            printf("No data within third seconds.\n");
            continue;
        }

        while(read(fd,&ev,sizeof(struct input_event)) == sizeof(struct input_event))
        {

        
            if(ev.type == EV_KEY)
            {
                printf("EV_KEY : code->%d  value->%d\r\n",ev.code,ev.value);
                if(ev.code < (int)(sizeof(key_names)/sizeof(char*)))
                {
                    printf("Key name : %s\r\n",key_names[ev.code]);
                }
                else if(ev.type == EV_SYN && ev.code == SYN_REPORT)
                {
                    printf("时间结束");
                }

                printf("\r\n");
            }
        }
        /* code */

    }
    


    close(fd);
    return 0;
}