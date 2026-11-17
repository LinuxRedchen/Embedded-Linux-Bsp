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


void Init(key_info *s)
{
    s -> mode = 0x01;
    s -> val = 'w';
    s -> gpio.GPIO_Group = 'A';
    s -> gpio.GPIO_Val = 2;

}

int main(void)
{
    key_info Key_up;

    Init(&Key_up);
    printf("val = %c\n",Key_up.val);
    printf("mode = %#04x\n",Key_up.mode);
    printf("group = %c\n",Key_up.gpio.GPIO_Group);
    printf("gpio = %d\n",Key_up.gpio.GPIO_Val);

}