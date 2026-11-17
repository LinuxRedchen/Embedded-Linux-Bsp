#include <stdio.h>

#define func()\
{\
    printf("这是多行宏第一句\n");\
    printf("这是多行宏第二个语句\n");\
}
int main(void)
{   
    func();

    return 0;
}