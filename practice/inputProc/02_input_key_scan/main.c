#include <linux/input-event-codes.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <linux/input.h>
#include <string.h>

#define NameMax 256




int main(int argc,char **argv)
{

    int fd;
    struct input_id infoID;
    int err;
    char dev_name[NameMax];
    unsigned int keybit[8];
    int len ;
    unsigned char byte;
    int i,bit;
    char *key_names[] = {
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

    if(argc != 2)
    {
        printf("Usage : %s <dev>!\r\n",argv[0]);
        return -1;
    }

    fd = open(argv[1],O_RDONLY);

    if(fd < 0)
    {
        printf("error : dev not open!\r\n");
        return -1;
    }
    err = ioctl(fd,EVIOCGID,&infoID);

    if(err < 0)
    {
        perror( "ioctl EVIOCGID" );
        close(fd);
        return -1;
    }
    else
    {
        printf("bustype = 0x%x\r\n",infoID.bustype);
	    printf("vendor  = 0x%x\r\n",infoID.vendor);
	    printf("product = 0x%x\r\n",infoID.product);
	    printf("version = 0x%x\r\n",infoID.version);
    }

    memset(dev_name,0,sizeof(dev_name));
    err = ioctl(fd,EVIOCGNAME(sizeof(dev_name)),dev_name);
    if(err < 0)
    {
        perror( "ioctl EVIOCGNAME" );
        close(fd);
        return -1;
    }
    else
    {
        printf("devname = %s\r\n",dev_name);
    }

    memset(keybit,0,sizeof(keybit));
    len = ioctl(fd,EVIOCGBIT(EV_KEY,sizeof(keybit)),keybit);

    if(len < 0)
    {
        perror("getbit");
        close(fd);
        return -1;
    }
    for(i=0;i<sizeof(keybit);i++)
    {
        byte = ((unsigned char *)keybit)[i];
        for(bit = 0;bit<8;bit++)
        {
            if(byte & (1<<bit))
            {
                int keycode = i*8 + byte;
                if(keycode < sizeof(key_names)/sizeof(char *))
                {
                    printf("%s    ",key_names[keycode]);
                }
                else
                {
                    printf("KEY(%d)  ", keycode);
                }
            }
        }
        printf("\n");

    }
    close(fd);

    return 0;
}