/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    IIC.c
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#include "IIC.h"
#include "delay.h"

void IIC_Init(void)
{
    IIC_DeviceInit();
}

static uint8_t IIC_ReadOneByte(uint8_t BaseAddr, uint8_t OffsetAddr)
{
    uint8_t ResultData = 0;
    IIC_DeviceStart();  

    IIC_DeviceSendByte(SLAVE_ADDR_WRITE);
    IIC_DeviceWaitAck();
    
    IIC_DeviceSendByte(BaseAddr);
    IIC_DeviceWaitAck(); 
    
    IIC_DeviceSendByte(OffsetAddr);
    IIC_DeviceWaitAck();
    
    IIC_DeviceStart();
    IIC_DeviceSendByte(SLAVE_ADDR_READ);
    IIC_DeviceWaitAck();     
    ResultData = IIC_DeviceReadByte(0);
    IIC_DeviceStop();
    
    return ResultData;
}

void IIC_WriteOneByte(uint8_t BaseAddr, uint8_t OffsetAddr, uint8_t Data)
{
    IIC_DeviceStart();  
    IIC_DeviceSendByte(SLAVE_ADDR_WRITE);
    IIC_DeviceWaitAck();
    
    IIC_DeviceSendByte(BaseAddr);
    IIC_DeviceWaitAck();
    
    IIC_DeviceSendByte(OffsetAddr);
    IIC_DeviceWaitAck();
    
    IIC_DeviceSendByte(Data);
    IIC_DeviceWaitAck();
    
    IIC_DeviceStop();
    delay_ms(10);
}

void IIC_CheckDevice(void)
{

}

boolean_t IIC_ReadData(uint8_t BaseAddr, uint8_t OffsetAddr, uint8_t *Buffer, uint16_t Length)
{
    boolean_t ResCode = S_FALSE;
    
    if (Length > 0) {
         for ( ; Length > 0; Length--) {
            *Buffer = IIC_ReadOneByte(BaseAddr, OffsetAddr);
            OffsetAddr++;
            Buffer++;
        }
        if (0 == ResCode) ResCode = S_TRUE;
    }
    return ResCode;
}

void IIC_WriteData(uint8_t BaseAddr, uint8_t OffsetAddr, uint8_t *Buffer, uint16_t Length)
{
    for ( ; Length > 0; Length--) {
        IIC_WriteOneByte(BaseAddr, OffsetAddr, *Buffer);
        OffsetAddr++;
        Buffer++;
    }
}
