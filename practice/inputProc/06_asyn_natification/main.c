#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <linux/input.h>
#include <signal.h>
#include <fcntl.h>


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

struct input_id id;
struct input_event ev;
unsigned char keybit[KEY_MAX / 8 +1];
int ret,len;
int i,bit;
unsigned char keycode;

int has_event;

void print_devinfo(int tfd)
{
    ret = ioctl(tfd,EVIOCGID,&id);

    if(ret < 0)
    {
        perror("EVIOCGID");
        close(tfd);
        return;
    }

    printf("ID:\r\nbustype->0x%x\r\nvendor->0x%x\r\nproduct->0x%x\r\nversion->0x%x\r\n",id.bustype,id.vendor,id.product,id.version);

}  

void print_key(int tfd)
{
    len = ioctl(tfd,EVIOCGBIT(EV_KEY,sizeof(keybit)),keybit);

    if(len < 0)
    {
        perror("EVIOCGBIT");
        close(tfd);
        return;
    }

    if(len <= sizeof(keybit) && len > 0)
    {
        for(i=0;i<len;i++)
        {
            keycode = keybit[i];
            for(bit =0;bit<8;bit++)
            {
                if(keycode & (1<<bit))
                {
                    keycode = i*8+bit;
                    if(keycode <= (sizeof(key_names)/sizeof(char*)))
                    {
                        printf("%s  ",key_names[keycode]);
                    }
                    else
                    {
                        printf("KEY(%d)",keycode);
                    }
                }
            }
        }
    }

}

void sigio_handler(int sig)
{
    (void)sig;
    has_event = 1;
}

int main(int argc,char **argv)
{
    int fd;
    int flag;
    ssize_t rrt;
    struct input_event ev;

    if(argc != 2)
    {
        printf("Usage : %s </dev/xxx> \r\n",argv[0]);
        return -1;
    }

    fd = open(argv[1],O_RDONLY | O_NONBLOCK);

    if(fd < 0)
    {
        perror("open file");
        return -1;
    }

    print_devinfo(fd);

    print_key(fd);

    signal(SIGIO, sigio_handler);

    fcntl(fd,F_SETOWN,getpid());

    flag = fcntl(fd,F_GETFL);
    fcntl(fd,F_SETFL,flag | FASYNC);

    while(1)
    {
        if(has_event == 1)
        {
            has_event = 0;

            while((rrt = read(fd,&ev,sizeof(struct input_event))) == sizeof(struct input_event))
            {
                if(ev.type == EV_KEY)
                {
                    printf("name : code->%d   value->%d",ev.code,ev.value); 
                    if(ev.code < (int)(sizeof(key_names)/sizeof(char*)))
                    {   
                        printf("%s   ",key_names[ev.code]);
                    }               
                    
                }
                else if (ev.type == EV_SYN && ev.code ==SYN_REPORT)
                    {
                        printf("finshed");
                    }

            
            printf("\r\n");
            if(rrt < 0)
            {
                perror("read");
            }
        }
    }

    close(fd);

    return 0;
}
}



