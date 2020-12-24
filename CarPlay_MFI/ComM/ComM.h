/*! ******************************************************************
 * .FILE_HEADER
 **********************************************************************
 * @file    ComM.h
 * @author  sumuhan, RD SW Platform
 * @owner   sumuhan, RD SW Platform
 * @date    2020-12-24
 * @brief   diagnotice trouble code handling
 */
/*! *******************************************************************/
#ifndef __COMM_H__
#define __COMM_H__
#include "IIC.h"
#include "Usart.h"

#define COMM_DATA_MAX_LEN     512

typedef enum {
    RespCode_CheckSumError = 0x01,
    RespCode_Nomal         = 0xFF
} ComM_RespCode_Type;

typedef enum {
    IIC_Write = 0x00,
    IIC_Read = 0x01
} ComM_IIC_Channel_Tpye;

typedef enum {
    ComM_Status_IDLE,
    ComM_Status_TX,
    ComM_Status_SESP,
} ComM_Status_Type;

typedef struct {
    uint8_t           ResqCode;
    uint8_t           RespCode;
    uint8_t           OffestAddr;
    uint8_t           ResqLength;
    uint8_t           CheckSum;
} ComM_Head_Type;

typedef struct {
    ComM_Status_Type  Status;
    ComM_Head_Type    Head;
    uint8_t           ComM_Buffer[COMM_DATA_MAX_LEN];
} ComM_Runtime_Type;

void ComM_Init(void);
void ComM_MainFunction(void);

#endif //__COMM_H__
