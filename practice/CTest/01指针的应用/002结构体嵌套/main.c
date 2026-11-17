#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    char GPIO_Group;
    uint32_t GPIO_Val;
} GPIO_INFO;

typedef struct{
    char val;
    uint32_t mode;
    GPIO_INFO gpio;
}key_info;


int main(void)
{
    key_info Key_up;
    key_info *up_addr = &Key_up;

    up_addr -> mode = 0x01;
    up_addr -> val = 'w';
    up_addr -> gpio.GPIO_Group = 'A';
    up_addr -> gpio.GPIO_Val = 2;
    printf("val = %c\n",Key_up.val);
    printf("mode = %#04x\n",Key_up.mode);
    printf("group = %c\n",Key_up.gpio.GPIO_Group);
    printf("gpio = %d\n",Key_up.gpio.GPIO_Val);

}