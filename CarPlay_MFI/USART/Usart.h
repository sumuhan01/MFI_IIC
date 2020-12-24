/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    Usart.h
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#ifndef __USART_H__
#define __USART_H__
#include "UserTypes.h"

void Usart_Init(void);
void Usart_MainFuction(void);
void Usart_RegisterReceiverReception(void (*Recept)(uint8_t *Buffer, uint16_t Length));
void Usart_SendData(uint8_t *Buffer,uint16_t Length);

#endif  //__USART_H__
