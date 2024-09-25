/**
  ******************************************************************************
  * @file    mb85rs64.h
  * @author  TUSI
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MB85RS64_H
#define __MB85RS64_H

#include "spiapi.h"

#define FRAM_OK         0   
#define FRAM_NOTAGERR   (-1)
#define FRAM_ERR        (-2)

/* fram指令 */
#define FRAM_WREN                   0x06
#define FRAM_WRDI                   0x04
#define FRAM_RDSR                   0x05
#define FRAM_WRSR                   0x01
#define FRAM_READ                   0x03
#define FRAM_WRITE                  0x02
#define FRAM_RDID                   0x9f
 
/* Defines ------------------------------------------------------------------*/
#define MB85RS64_SIZE               (1024 * 32)              /* 实际使用的是FM25L16B */
#define FM_SIZE                     (MB85RS64_SIZE)

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported functions ------------------------------------------------------- */
#define FM_Read(offset,buf,len)     MB85RS_Read(offset,buf,len)
#define FM_Write(offset,buf,len)    MB85RS_Write(offset,buf,len)

int MB85RS_Write(uint32_t offset, uint8_t *buf, uint32_t len);
int MB85RS_Read(uint32_t offset, uint8_t *buf, uint32_t len);
int MB85RS_RDID(uint8_t *id, int len);
int MB85RS_Init(int bus, int select);

#ifdef __cplusplus
}
#endif

#endif
