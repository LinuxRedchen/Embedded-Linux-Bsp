#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <linux/input.h>


int main(int argc , char **argv)
{
    int fd;
    int err;
    struct input_id id;
    unsigned int evbit[2];
    unsigned char byre;
    int len;
    int i ;
    char *ev_names[] ={
    "EV_SYN",
    "EV_KEY",
    "EV_REL",
    "EV_ABS",
    "EV_MS",
    "EV_SW",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
    "EV_LED",
    "EV_SND",
    "NULL",
    "EV_REP",
    "EV_FF",
    "EV_PWR"
    };
    
    if(argc != 2)
    {
        printf("Usage : %s <dev>\n",argv[2]);
        return -1;
    }

    fd = open(argv[1],O_RDWR);

    if(fd < 0 )
    {
        printf("can not open %s !",argv[1]);
        return -1;
    }

    err = ioctl(fd,EVIOCGID,&id);
    if(err == 0)
    {
        printf("bustype = 0x%x\n", id.bustype);
        printf("vendor  = 0x%x\n", id.vendor);
        printf("product = 0x%x\n", id.product);
        printf("version = 0x%x\n", id.version);

    }
    len = ioctl(fd , EVIOCGBIT(0,sizeof(evbit)),&evbit);

    if(len > 0 && len <= sizeof(evbit))
    {
        for (i =0;i<len ;i++){
            byre =((unsigned char *)evbit)[i];
            for(int bit = 0;bit <8;bit++)
            {
                if(byre & (1<<bit))
                {
                    printf("%s ",ev_names[i*8 + bit]);
                }
            }
        }
    }


    return 0;
}
