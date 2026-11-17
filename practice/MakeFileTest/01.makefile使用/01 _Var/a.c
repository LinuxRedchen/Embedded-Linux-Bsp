#include <stdio.h>

extern func_b(void);
extern func_c(void);

int main()
{

    printf("This is a!\r\n");
    func_b();
    func_c();

}