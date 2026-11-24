#include <sys/poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <poll.h>


int fd;

struct input_id id;

unsigned char key_bit[KEY_MAX / 8 +1];
unsigned char keycode;
int retid;
int retkey;

int i,bit;

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

struct pollfd tfd[1];

void print_devid(int fd)
{
    retid = ioctl(fd,EVIOCGID,&id);

    if(retid < 0)
    {
        perror("getid");
        close(fd);
        return ;
    }

    printf("id:bustype->0x%x  vendor->0x%x  product->0x%x  version->0x%x\r\n",id.bustype,id.vendor,id.product,id.version);
}

void print_support_key(int fd)
{
    retkey = ioctl(fd,EVIOCGBIT(EV_KEY,sizeof(key_bit)),key_bit);

    if(retkey < 0)
    {
        perror("getbit");
        close(fd);
        return ;
    }

    if(retkey > 0 && retkey < sizeof(key_bit))
    {
        for(i = 0; i<retkey;i++)
        {
            keycode = key_bit[i];
            for(bit = 0;bit <8;bit++)
            {
                if(keycode & (1 << bit))
                {
                    keycode = i * 8 + bit;
                    if(keycode < (int)(sizeof(key_names)/sizeof(char*)))
                    {
                        printf("%s  ",key_names[keycode]);
                    }
                    else
                    {
                        printf("KEY(%d)  ",keycode);
                    }

                }
                
                
            }
        }
        printf("\r\n");
    }
}

int main(int argc,char **argv)
{
    int poll_ret;
    int rret;
    struct input_event ev;

    if(argc != 2)
    {
        printf("Usage : %s <dev>\r\n",argv[0]);
        return -1;
    }
    fd = open(argv[1],O_RDONLY);

    if(fd < 0)
    {
        perror("read");
        return -1;
    }

    print_devid(fd);

    print_support_key(fd);

    tfd[0].fd = fd;
    tfd[0].events = POLLIN;

    while(1)
    {
        
        poll_ret = poll(tfd,sizeof(tfd),1000);    

        if(poll_ret < 0)
        {
            perror("poll");
            close(fd);
            return -1;
        } 
        if(poll_ret == 0)
        {
            printf("do other thing!\r\n");
            continue;
        }   

        if(tfd[0].revents & POLLIN)
        {
            while((rret = read(fd,&ev,sizeof(struct input_event))) ==  sizeof(struct input_event))
            {
                if(ev.type == EV_KEY)
                {
                    printf("name:code->%d value->%d\r\n",ev.code,ev.value);
                    if(ev.code < (int)(sizeof(key_names)/sizeof(char*)))
                    {
                        printf("name:%s\r\n",key_names[ev.code]);
                    }
                    else
                    {
                        printf("fished!");
                    }
                }
            }
        }
        
    }




    close(fd);
    return 0;
}