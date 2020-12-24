/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    Usart_Device.h
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#ifndef __USART_DEVICE_H__
#define __USART_DEVICE_H__
#include "stm32f10x.h"
#include "UserTypes.h"

//define date 
#define USART_DATA_MAX_LEN     512
#define USART_BAUDRATE         115200

typedef struct {
    uint8_t      Usart_ReceStart;
    uint8_t      Usart_ReceStop;
    uint8_t      Usart_HeadCount;
    uint8_t      Usart_ReceCount;
    uint16_t     Usart_ReceLength;
    uint8_t      Usart_DataBuff[USART_DATA_MAX_LEN];
    void         (*Usart_Recv)(uint8_t *Buffer, uint16_t Len);
} UsartRuntimeType;

void Usart_DeviceInit(void);

extern UsartRuntimeType Usart_Runtime;
#define usart_runtime Usart_Runtime

#endif  //__USART_DEVICE_H__
