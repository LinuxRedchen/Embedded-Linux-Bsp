#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

typedef struct 
{
    uint32_t CTRL;
    uint32_t STA;
    uint32_t RSV;
}Reg;


#define my_offsetof(Type,number) ((size_t)(&(((Type *)0) ->number)))

int main(void)
{
    printf("my %zu\r\n",my_offsetof(Reg,RSV));
    printf("sys %zu\r\n",offsetof(Reg,RSV));
    return 0;
}