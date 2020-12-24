/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    IIC_Device.c
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#include "IIC_Device.h"
#include "delay.h"

static void IIC_DeviceInitGpio(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(    RCC_APB2Periph_GPIOB, ENABLE );
       
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);     //PB6,PB7 输出高
}

void IIC_DeviceStart(void)
{
    SDA_OUT();
    IIC_SDA=1;
    IIC_SCL=1;
    delay_us(4);
    IIC_SDA=0;
    delay_us(4);
    IIC_SCL=0;
}

void IIC_DeviceStop(void)
{
    SDA_OUT();
    IIC_SCL=0;
    IIC_SDA=0;
     delay_us(4);
    IIC_SCL=1; 
    IIC_SDA=1;
    delay_us(4);
}

void IIC_DeviceAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=0;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    IIC_SCL=0;
}

void IIC_DeviceNAck(void)
{
    IIC_SCL=0;
    SDA_OUT();
    IIC_SDA=1;
    delay_us(2);
    IIC_SCL=1;
    delay_us(2);
    IIC_SCL=0;
}

uint8_t IIC_DeviceWaitAck(void)
{
    uint8_t ucErrTime=0;
    SDA_IN();
    IIC_SDA=1;delay_us(1);
    IIC_SCL=1;delay_us(1);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            IIC_DeviceStop();
            return 1;
        }
    }
    IIC_SCL=0;
    return 0; 
}


void IIC_DeviceSendByte(uint8_t data)
{                        
    uint8_t index;   
    SDA_OUT();         
    IIC_SCL=0;//拉低时钟开始数据传输
    for(index = 0; index < 8; index++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
        if((data&0x80)>>7)
            IIC_SDA=1;
        else
            IIC_SDA=0;
        data<<=1;       
        delay_us(2);
        IIC_SCL=1;
        delay_us(2); 
        IIC_SCL=0;    
        delay_us(2);
    }
}

u8 IIC_DeviceReadByte(unsigned char data)
{
    unsigned char i,receive=0;
    SDA_IN();
    for(i=0;i<8;i++ )
    {
        IIC_SCL=0; 
        delay_us(2);
        IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
        delay_us(1); 
    }                     
    if (!data)
        IIC_DeviceNAck();
    else
        IIC_DeviceAck();
    return receive;
}

void IIC_DeviceInit(void)
{
    IIC_DeviceInitGpio();
}
