#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    volatile uint32_t CFG;
    volatile uint32_t DATA;
    volatile uint32_t EVENT;
    volatile uint32_t RESERVED;
    volatile uint32_t INT_MASK;
}RegInfo;

#define DevReg ((RegInfo *)(0x42004000))

void dev_cfg_enable(bool en)
{
    uint32_t tempVal = DevReg->CFG;
    if(en)
    {
        tempVal |= (1u << 0);
    }
    else
    {
        tempVal &= ~(1u << 0);
    }
    DevReg->CFG = tempVal;
}

void dev_set_timeout(uint8_t val)
{
    uint32_t tempVal = DevReg->CFG;
    tempVal &= ~(0xFU << 4);
    tempVal |= (((uint32_t)val) << 4) ;
    DevReg->CFG = tempVal;
}

uint32_t dev_read_data(void)
{
    return DevReg->DATA;
}

void dev_clear_event(void)
{
    DevReg->EVENT = ~(1u << 2);
}

void dev_set_int_mask(bool mask_en)
{
    uint32_t tempVal = DevReg->INT_MASK;
    if(mask_en)
    {
        tempVal |= (1u << 0);
    }
    else
    {
        tempVal &= ~(1u << 0);
    }
    DevReg->INT_MASK = tempVal;
}

int main(void)
{

    return 0;
}