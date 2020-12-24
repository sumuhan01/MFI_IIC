#include "ComM.h"
#include "delay.h"

int main(void)
{
    delay_init();
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    ComM_Init();

    while(1)
    {
        ComM_MainFunction();
    }
}

