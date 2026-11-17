#include "headfile.h"

int x = 2, y = 4;
char c[] = "number";

int main(void)
{
    printf("%d+%d=%d\n",x,y,sumProc(x,y));
    print(c);
    return 0;
}