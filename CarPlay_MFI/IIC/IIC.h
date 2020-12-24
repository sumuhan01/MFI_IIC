/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    IIC.h
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#ifndef __IIC_H__
#define __IIC_H__
#include "IIC_Device.h"

#define SLAVE_ADDR_READ    0xA1u  //写从设备
#define SLAVE_ADDR_WRITE   0xA0u  //读从设备

void IIC_Init(void);
boolean_t IIC_ReadData(uint8_t BaseAddr, uint8_t OffsetAddr, uint8_t *Buffer, uint16_t Length);
void IIC_WriteData(uint8_t BaseAddr, uint8_t OffsetAddr, uint8_t *Buffer, uint16_t Length);

#endif //__IIC_H__
