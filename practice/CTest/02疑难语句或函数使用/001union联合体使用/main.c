#include <stdio.h>

union box
{
    int a;
    int b;
    int c;
    char val;
};


int main(void)
{
    union box x1;
    x1.a=0x123456;
    printf("a:%#x\n",x1.a);
    x1.b=0x88;
    printf("a:%#x\n",x1.a);
    printf("b:%#x\n",x1.b);
    return 0;
}