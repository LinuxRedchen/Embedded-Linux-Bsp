#include <stdio.h>
#include <stdint.h>

typedef struct
{
    volatile uint32_t dev_CTRL;
    volatile uint32_t dev_STATUS;
}Dev;

#define Dev_BASS ((Dev *)0x20001000)

void hw_enable(void)
{
    uint32_t temp = Dev_BASS->dev_CTRL;
    temp |= (1u<<0);
    temp |= (0u<<1);
    Dev_BASS->dev_CTRL = temp;
}

void hw_disable(void)
{
    uint32_t temp = Dev_BASS->dev_CTRL;
    temp |= (0u<<0);
    temp |= (0u<<1);
    Dev_BASS->dev_CTRL = temp;
}

void hw_set_cfg(uint8_t val)
{
    uint32_t temp = Dev_BASS->dev_CTRL;
    temp |= (val << 8);
    Dev_BASS->dev_CTRL = temp;
}

int hw_is_interrupt_pending(void)
{
    uint32_t temp = Dev_BASS->dev_STATUS;
    if(temp & (1u << 1))
    {
        temp |= (1u << 1);
        Dev_BASS->dev_STATUS=temp;
    }
    if(temp & (1u << 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main(void)
{

    return 0;

}

/*\正确代码
#include <stdint.h>

typedef struct
{
    volatile uint32_t dev_CTRL;
    volatile uint32_t dev_STATUS;
}Dev;

#define Dev_BASE ((Dev *)0x20001000)

//使能外设，关闭中断；其它bit不变
void hw_enable(void)
{
    uint32_t temp = Dev_BASE->dev_CTRL;
    temp |=  (1U << 0);         //bit0置1打开外设
    temp &= ~(1U << 1);         //bit1清零关闭中断
    Dev_BASE->dev_CTRL = temp;
}

//关闭外设，关闭中断；其它bit不变
void hw_disable(void)
{
    uint32_t temp = Dev_BASE->dev_CTRL;
    temp &= ~(1U << 0);         //bit0清零关闭外设
    temp &= ~(1U << 1);         //bit1清零关闭中断
    Dev_BASE->dev_CTRL = temp;
}

//设置CTRL寄存器8‑15位配置参数
void hw_set_cfg(uint8_t val)
{
    uint32_t temp = Dev_BASE->dev_CTRL;
    uint32_t mask = ~(0xFFU << 8);
    temp &= mask;                       //清除旧的bit8‑15
    temp |= ((uint32_t)val << 8);       //写入新值
    Dev_BASE->dev_CTRL = temp;
}

//读取STATUS，中断pending bit1，为1返回1并且写1清零；否则返回0
int hw_is_interrupt_pending(void)
{
    uint32_t temp = Dev_BASE->dev_STATUS;
    if(temp & (1U << 1))
    {
        Dev_BASE->dev_STATUS = (1U << 1); //W1C，只写bit1置1清除pending
        return 1;
    }
    return 0;
}


*/