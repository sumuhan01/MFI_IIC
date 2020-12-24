/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    Usart_Device.c
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#include "Usart_Device.h"

UsartRuntimeType Usart_Runtime;

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
    /* 发送一个字节数据到串口 */
    USART_SendData(USART1, (uint8_t) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);        
    return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
    return (int)USART_ReceiveData(USART1);
}

static void Usart_DeviceInitGpio(void)
{
    GPIO_InitTypeDef GPIO_Struct;
    USART_InitTypeDef USART_Struct;
    NVIC_InitTypeDef NVIC_Struct;
     
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
  
    //USART1_TX   GPIOA.9
    GPIO_Struct.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_Struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Struct.GPIO_Mode = GPIO_Mode_AF_PP;    //复用推挽输出
    GPIO_Init(GPIOA, &GPIO_Struct);//初始化GPIOA.9
   
    //USART1_RX      GPIOA.10初始化
    GPIO_Struct.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_Struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_Struct);//初始化GPIOA.10  

    //Usart1 NVIC 配置
    NVIC_Struct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 3 ;
    NVIC_Struct.NVIC_IRQChannelSubPriority = 3;
    NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_Struct);
  
   //USART 初始化设置
    USART_Struct.USART_BaudRate = USART_BAUDRATE;
    USART_Struct.USART_WordLength = USART_WordLength_8b;
    USART_Struct.USART_StopBits = USART_StopBits_1;
    USART_Struct.USART_Parity = USART_Parity_No;
    USART_Struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;    //收发模式
    
    USART_Init(USART1, &USART_Struct);
    
    //开启接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE); 
}

void USART1_IRQHandler(void)
{
    uint8_t tempData = 0;
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        tempData = USART_ReceiveData(USART1);
        if (usart_runtime.Usart_ReceStart != 0) {
            if (usart_runtime.Usart_ReceStop != 1) {
                if (usart_runtime.Usart_ReceCount < usart_runtime.Usart_ReceLength) {
                    usart_runtime.Usart_DataBuff[usart_runtime.Usart_ReceCount] = tempData;
                    usart_runtime.Usart_ReceCount++;
                } else {
                    usart_runtime.Usart_ReceStop = 1;
                    usart_runtime.Usart_ReceCount = 0;
                }
            }
        } else {
            if (usart_runtime.Usart_HeadCount == 0) {
                usart_runtime.Usart_ReceLength = (tempData << 8) & 0xFF00;
                usart_runtime.Usart_HeadCount++;
            } else if (usart_runtime.Usart_HeadCount == 1) {
                usart_runtime.Usart_ReceLength |= tempData;
                usart_runtime.Usart_ReceStart = 1;
                usart_runtime.Usart_HeadCount = 0;
            }
        }
     }
}

void Usart_DeviceInit(void)
{
    memset(&Usart_Runtime, 0x00, sizeof(Usart_Runtime));
    Usart_DeviceInitGpio();
}
