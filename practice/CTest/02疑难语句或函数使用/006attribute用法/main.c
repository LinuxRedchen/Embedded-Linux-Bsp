#include <stdio.h>
#include <stdint.h>

/*
__attribute((packed))用法:取消自动填充，内存对齐
__attribute((aligned(n)))用法:增大对齐的最小字节倍数n
__attribute((unused))用法:让未使用的函数或者变量不报警告
__attribute((section("xxx")))用法:让声明的变量存向自定义的xxx段，例如__attribute((section(".my_data")))，存向my_data段
gcc main.c -o test.elf
objdump -t test.elf
*/

int a __attribute((unused));
typedef struct __attribute((packed))
{
    uint8_t a;
    uint8_t b;
}S;
S test __attribute((aligned(8)));
int asd __attribute((section(".my_space")));
int main(void)
{

    S *add = &test;
    printf("add:%p",add);


    return 0;

}