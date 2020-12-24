/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    IIC_Device.h
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#ifndef __IIC_DEVICE_H__
#define __IIC_DEVICE_H__
#include "stm32f10x.h"
#include "UserTypes.h"


#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)3<<28;}

#define IIC_SCL    PBout(6)
#define IIC_SDA    PBout(7)
#define READ_SDA   PBin(7)

void IIC_DeviceInit(void);
void IIC_DeviceStart(void);
void IIC_DeviceStop(void);
void IIC_DeviceAck(void);
void IIC_DeviceNAck(void);
uint8_t IIC_DeviceWaitAck(void);

void IIC_DeviceSendByte(uint8_t data);
uint8_t IIC_DeviceReadByte(unsigned char data);

#endif  //__IIC_DEVICE_H__
