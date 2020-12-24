/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    Usart.c
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#include "Usart.h"
#include "Usart_Device.h"

void Usart_RegisterReceiverReception(void (*Recept)(uint8_t *Buffer, uint16_t Length))
{
    usart_runtime.Usart_Recv = Recept;
}

static void Usart_RecvProc() 
{
    if (usart_runtime.Usart_ReceStop == 1 && 
        usart_runtime.Usart_ReceStart == 1) {
        if (usart_runtime.Usart_Recv) {
            usart_runtime.Usart_Recv(usart_runtime.Usart_DataBuff,
            usart_runtime.Usart_ReceLength);
        }
        usart_runtime.Usart_ReceStop = 0;
        usart_runtime.Usart_ReceStart = 0;
    }
}

static void Usart_SendOneByte(uint8_t data)
{
    USART_SendData(USART1, (uint16_t)data);
}

void Usart_SendData(uint8_t *Buffer,uint16_t Length)
{
    for (; Length > 0; Length--) {
        Usart_SendOneByte(*Buffer);
        Buffer++;
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
    }
}

void Usart_Init(void)
{
    Usart_DeviceInit();
}

void Usart_MainFuction(void)
{
    Usart_RecvProc();
}
