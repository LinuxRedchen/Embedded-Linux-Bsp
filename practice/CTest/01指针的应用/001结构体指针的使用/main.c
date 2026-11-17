#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct{
    char val;
    uint32_t mode;

}key_info;


int main(void)
{
    key_info Key_up;
    key_info *up_addr = &Key_up;

    up_addr -> mode = 0x01;
    up_addr -> val = 'w';

    printf("val = %c\n",Key_up.val);
    printf("mode = %#04x\n",Key_up.mode);


}