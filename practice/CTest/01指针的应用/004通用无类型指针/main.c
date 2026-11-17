#include <stdio.h>
#include <stdint.h>

void *p;

uint32_t key = 200;
uint32_t val = 300;
uint32_t *st = &val;
uint32_t *s = NULL;

uint32_t sum_A_B(void *a,void *b)
{
    return *((uint32_t *)a)+*((uint32_t *)b);
}

int main(void)
{
    s = &key;
    p = st;
    printf("p = %d\r\n",*(uint32_t *)p);
    printf("sum = %d\r\n",sum_A_B(st,s));
    return 0;
}