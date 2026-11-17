#include <stdint.h>
#include <stdio.h>
#include <stdint.h>

typedef struct __attribute__((packed))
{
    char a;
    uint32_t b;
}A;

typedef struct
{
    char a;
    uint32_t b;
}B;


int main(void)
{
    A Apptest;
    B Addtest;

    printf("联合体内存 = %ld\n",sizeof(Apptest));
    printf("结构体内存 = %ld\n",sizeof(Addtest));

    return 0;
}