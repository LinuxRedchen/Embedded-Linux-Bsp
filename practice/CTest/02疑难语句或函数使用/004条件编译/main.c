#include <stdio.h>

#define Board_STM32

#ifdef Board_STM32
void func(void)
{
    printf("这是STM32的条件编译\n");
}
#elif defined (Board_Imx6ull)
void func(void)
{
    printf("这是Imx6ull的条件编译\n");
}
#else
void func(void)
{
    printf("没有任何的条件编译\n");
}
#endif

int main(void)
{
    func();
    return 0;
}