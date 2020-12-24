/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    ComM.c
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#include "ComM.h"

ComM_Runtime_Type comm_runtime;

static uint8_t ComM_ChecksumCalc(uint8_t *Buffer, uint8_t Length)
{
    uint32_t DataSum = 0;
    for (; Length > 0; Length--) {
        DataSum += *Buffer++;
    }
    return DataSum % 256;
}

static void ComM_ReceiverUsart(uint8_t *Buffer, uint16_t Length)
{
    comm_runtime.Head.CheckSum = ComM_ChecksumCalc(Buffer,Length-1);
    if (Buffer[Length-1] == comm_runtime.Head.CheckSum) {
        if ( ComM_Status_IDLE == comm_runtime.Status) {
            comm_runtime.Head.ResqCode = Buffer[0];
            comm_runtime.Head.OffestAddr = Buffer[1];
            comm_runtime.Head.ResqLength = Buffer[2];
            memcpy(&comm_runtime.ComM_Buffer, &Buffer[3], Length - 1);
            comm_runtime.Status = ComM_Status_TX;
        }
    } else {
        comm_runtime.Head.RespCode = RespCode_CheckSumError;
        comm_runtime.Status = ComM_Status_SESP;
        comm_runtime.Head.CheckSum = ComM_ChecksumCalc((uint8_t *)comm_runtime.Status,1);
    }
}

static void ComM_TransmitToIICProc(void) 
{
    if (ComM_Status_TX == comm_runtime.Status) {
        if (IIC_Write == comm_runtime.Head.ResqCode) {  //BaseAddr default 0x00
            IIC_WriteData(0x00,comm_runtime.Head.OffestAddr
            ,comm_runtime.ComM_Buffer, comm_runtime.Head.ResqLength);
            comm_runtime.Status = ComM_Status_IDLE;
        } 
        else if (IIC_Read == comm_runtime.Head.ResqCode) {
            if (S_TRUE == IIC_ReadData(0x00,comm_runtime.Head.OffestAddr
            ,comm_runtime.ComM_Buffer, comm_runtime.Head.ResqLength)) {
                comm_runtime.Head.RespCode = RespCode_Nomal;
                comm_runtime.Status = ComM_Status_SESP;
            }
        }
    }
}

static void ComM_ResponseToUsartProc(void)
{
    if (ComM_Status_SESP == comm_runtime.Status) {
        if (RespCode_Nomal == comm_runtime.Head.RespCode) {
            uint8_t tempData[COMM_DATA_MAX_LEN] = {0};
            tempData[0] = comm_runtime.Head.RespCode;
            memcpy(&tempData[1], comm_runtime.ComM_Buffer, comm_runtime.Head.ResqLength);
            comm_runtime.Head.CheckSum = ComM_ChecksumCalc(tempData,comm_runtime.Head.ResqLength+1);
            tempData[comm_runtime.Head.ResqLength] = comm_runtime.Head.CheckSum;
            Usart_SendData(tempData, comm_runtime.Head.ResqLength+2);
        } else if (RespCode_CheckSumError == comm_runtime.Head.RespCode) {
            uint8_t tempData[2] = {0};
            tempData[0] = comm_runtime.Head.RespCode;
            tempData[1] = comm_runtime.Head.CheckSum;
            Usart_SendData(tempData,sizeof(tempData));
        }
        comm_runtime.Status = ComM_Status_IDLE;
    }
}

void ComM_Init(void)
{
    Usart_Init();
    IIC_Init();
    memset(&comm_runtime, 0x00, sizeof(comm_runtime));
    Usart_RegisterReceiverReception(ComM_ReceiverUsart);
}

void ComM_MainFunction(void)
{
    Usart_MainFuction();
    ComM_TransmitToIICProc();
    ComM_ResponseToUsartProc();
}
