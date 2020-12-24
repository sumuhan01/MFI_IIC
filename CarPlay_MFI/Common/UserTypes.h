#ifndef __USER_TYPES_H__
#define __USER_TYPES_H__

#ifndef BASIC_TYPE_DEFINE
#define BASIC_TYPE_DEFINE
#define S_TRUE           ((boolean_t) 1)
#define S_FALSE          ((boolean_t) 0)
#define S_NULL           ((void *) 0)

//address remap
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

////IO address remap GPIOA & GPIOB
//#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
//#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 

//#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
//#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 

//#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)
//#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)
//#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)

typedef unsigned char      boolean_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef unsigned char      bitfield_t;
#endif

#include <string.h>
#include "stdio.h"

#endif // __USER_TYPES_H__
