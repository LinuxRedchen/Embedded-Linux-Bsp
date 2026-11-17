#include <stdint.h>
#include <stdbool.h>

typedef struct 
{
    volatile uint32_t CTRL;
    volatile uint32_t STATUS;
    volatile uint32_t MASK;
}RegInfo;

#define DevReg ((RegInfo *)0x40020000)

void dev_module_enable(bool en)
{
    uint32_t TempVal = DevReg->CTRL;

    if(en)
    {
        TempVal |= (1u << 0);
        DevReg->CTRL = TempVal;
    }
    else
    {
        TempVal &= ~(1u << 0);
        DevReg->CTRL = TempVal;
    }
}

void dev_set_div(uint8_t div_val)
{
    uint32_t TempVal = DevReg->CTRL;
    TempVal &= ~(0xFU << 8);// 11111000 01111111     
    TempVal |= (((uint32_t)div_val) << 8);
    DevReg->CTRL = TempVal;
}

int dev_get_int_pending(void)
{
    uint32_t TempVal = DevReg->STATUS;
    if(TempVal & (1u << 2) && TempVal & (1u << 5))
    {
/*        TempVal = (1u << 2);
        TempVal |= (1u << 5);
        DevReg->STATUS = TempVal;*/
        return 5;
    }
    else if(TempVal & (1u << 2))
    {
/*      TempVal = (1u << 2);
//        DevReg->STATUS = TempVal;*/
        return 2;
    }
    else if(TempVal & (1u << 5))
    {
/*        TempVal = (1u << 5);
//        DevReg->STATUS = TempVal;*/
        return 5;
    }
    else
        return 0;
}

void dev_clear_int(uint32_t int_src)
{
    uint32_t TempVal = (1u << int_src);
    DevReg->STATUS = TempVal;
}

int main(void)
{



    return 0;
}