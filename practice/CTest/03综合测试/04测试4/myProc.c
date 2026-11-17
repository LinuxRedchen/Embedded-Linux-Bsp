/*
uint16_t 这个在0x05上，直接读取有bug，会死掉，采用指针读取大小端的位运算方法读取
uint16_t stat16_val;
volatile uint8_t *p = (volatile uint8_t *)0x52001000 + 0x05;
uint8_t lo = p[0];
uint8_t hi = p[1];
stat16_val = ( (uint16_t)hi << 8 ) | lo;
*/
#include <stdint.h>
#include <stdbool.h>

typedef struct __attribute__((packed))
{
    volatile uint32_t CTRL;
    volatile uint8_t CFG8;
    volatile uint16_t STAT16;
    volatile uint8_t RSV;
    volatile uint32_t EVENT_SET;
    volatile uint32_t EVENT_CLR;
}RegInfo;

#define DevRegister ((RegInfo *)(0x52001000))

void module_power_switch(bool en)
{
    uint32_t tempVal = DevRegister->CTRL;
    if(en)
    {
        tempVal |= ((uint32_t)1u << 0);
    }
    else
    {
        tempVal &= ~((uint32_t)1u << 0);
    }
    DevRegister->CTRL = tempVal;
}

void set_prescaler(uint8_t div_val)
{
    uint32_t tempVal = DevRegister->CTRL;
    tempVal &= ~((uint32_t)0x7U << 1); 
    tempVal |= ((uint32_t)div_val << 1);
    DevRegister->CTRL = tempVal;
}

void module_soft_reset(void)
{
    DevRegister->CTRL = ((uint32_t)1u << 8);
}

void cfg8_enable_err_report(bool en)
{
    uint8_t tempVal = DevRegister->CFG8;
    if(en)
    {
        tempVal |= ((uint8_t)1u << 0);
    }
    else
    {
        tempVal &= ~((uint8_t)1u << 0);
    }
    DevRegister->CFG8 = tempVal;
}

bool get_err_and_ready(bool *data_rdy_out)
{
    uint16_t tempVal = DevRegister->STAT16;
    if(tempVal & ((uint16_t)1u << 7))
    {
        *data_rdy_out = 1;
    }
    else
    {
        *data_rdy_out = 0;
    }
    if(tempVal & ((uint16_t)1u << 2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void generate_software_event(void)
{
    uint32_t tempVal = ((uint32_t)1u << 0);
    DevRegister->EVENT_SET = tempVal;
}

void clear_software_event(void)
{
    uint32_t tempVal = ((uint32_t)1u << 0);
    DevRegister->EVENT_CLR = tempVal;
}

int main(void)
{

    return 0;
}


