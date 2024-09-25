/**
  ******************************************************************************
  * @file    mb85rs64.c
  * @author  TUSI
  * @version V1.0.0
  * @date
  * @brief
  ******************************************************************************
*/ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "mb85rs64.h"

static uint8_t g_AddrBytes3 = 1;
static uint32_t g_Density = 0;

typedef struct {
    int bus;
    int select;
}MB85RS_t;
static MB85RS_t *g_pFRAM = NULL;

/**************************************************************************************
 *  Description: 通过SPI向从设备发送命令
 *   Input Args:   *txdata：向从设备发送命令的内容；
 *                 *rxdata：向从设备发送命令的内容；
 *  Output Args:
 * Return Value:
 *************************************************************************************/
 static int send_cmd(unsigned char *txdata, unsigned char *rxdata, int dataLen)
{
    int status = FRAM_ERR;
    
    if(!g_pFRAM)
        return status;

    status = spi_transfer(g_pFRAM->bus, g_pFRAM->select, txdata, rxdata, dataLen);
    if(status < 0) {
        perror("can't send command to device");
    }

    return status;
}

/*
* @brief  MB85RS_Read
* @param  None
* @retval None
*/
static int MB85RS_RDDATA(uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t ret = FRAM_ERR;
    uint8_t cmd_len;
    
    unsigned char cmd[4] = {0};
    cmd[0] = FRAM_READ;
    if(g_AddrBytes3) {
        cmd[1] = (uint8_t)((offset >> 16) & 0xff);
        cmd[2] = (uint8_t)((offset >> 8) & 0xff);
        cmd[3] = (uint8_t)(offset & 0xff);
        cmd_len = 4;
    } else {
        cmd[1] = (uint8_t)((offset >> 8) & 0xff);
        cmd[2] = (uint8_t)(offset & 0xff);
        cmd_len = 3;
    }

    uint32_t totallen = cmd_len + len;
    unsigned char *ptxData = (unsigned char *)malloc(totallen);
    unsigned char *prxData = (unsigned char *)malloc(totallen);
    if((ptxData)&&(prxData)){
        memset(ptxData, 0, totallen);
        memset(prxData, 0, totallen);
    
        memcpy(ptxData, cmd, cmd_len);
        int32_t spi_rt = send_cmd(ptxData, prxData, totallen);
        if(spi_rt < 0){
            printf("can't read data\n");
        }else{
            ret = FRAM_OK;
        }
        memcpy(buf, prxData+cmd_len, len);
    }
    
    if(ptxData){
        free(ptxData);
    }
    if(prxData){
        free(prxData);
    }
    
    return ret;
}

/*
* @brief  MB85RS_Write
* @param  None
* @retval None
*/
static int MB85RS_WRDATA(uint32_t offset, uint8_t *buf, uint32_t len)
{
    int32_t ret = FRAM_ERR;
    uint8_t cmd_len;
        
    unsigned char cmd[4] = {0};
    cmd[0] =  FRAM_WRITE;
    if(g_AddrBytes3) {
        cmd[1] = (uint8_t)((offset >> 16) & 0xff);
        cmd[2] = (uint8_t)((offset >> 8) & 0xff);
        cmd[3] = (uint8_t)(offset & 0xff);
        cmd_len = 4;
    } else {
        cmd[1] = (uint8_t)((offset >> 8) & 0xff);
        cmd[2] = (uint8_t)(offset & 0xff);
        cmd_len = 3;
    }

    uint32_t totallen = cmd_len + len;
    unsigned char *ptxData = (unsigned char *)malloc(totallen);
    if(ptxData){
        memset(ptxData, 0, totallen);
        
        memcpy(ptxData, cmd, cmd_len);
        memcpy(ptxData+cmd_len, buf, len);
        int32_t spi_rt = send_cmd(ptxData, NULL, totallen);
        if(spi_rt < 0){
            printf("can't write data\n");
        }else{
            ret = FRAM_OK;
        }
        free(ptxData);
    }
    
    return ret;
}

/*
* @brief  MB85RS_WREN
* @param  None
* @retval None
*/
static int MB85RS_WREN()
{
    int ret = FRAM_OK;
    
    unsigned char cmd = FRAM_WREN;
    int32_t spi_rt = send_cmd(&cmd, NULL, 1);
    if(spi_rt < 0){
        printf("can't send write enable cmd\n");
        ret = FRAM_ERR;
    }
    
    return ret;
}

/*
* @brief  MB85RS_WRDI
* @param  None
* @retval None
*/
static int MB85RS_WRDI()
{
    int ret = FRAM_OK;
    
    unsigned char cmd =  FRAM_WRDI;
    int32_t spi_rt = send_cmd(&cmd, NULL, 1);
    if(spi_rt < 0){
        printf("can't send write disable cmd\n");
        ret = FRAM_ERR;
    }
    
    return ret;
}

/*
* @brief  MB85RS_Write
* @param  None
* @retval None
*/
int MB85RS_Write(uint32_t offset, uint8_t *buf, uint32_t len)
{
    int status = FRAM_OK;
    
    status = MB85RS_WREN();
    if(status != FRAM_OK){
        return status;
    }
    
    status = MB85RS_WRDATA(offset, buf, len);
    if(status != FRAM_OK){
        printf("FRAM write opteration faild!");
    }
    
    status = MB85RS_WRDI();
    
    return status;
}

/*
* @brief  MB85RS_Read
* @param  None
* @retval None
*/
int MB85RS_Read(uint32_t offset, uint8_t *buf, uint32_t len)
{    
    return MB85RS_RDDATA(offset, buf, len);
}

/*
* @brief  MB85RS_RDID
* @param  None
* @retval None
*/
int MB85RS_RDID(uint8_t *id, int len)
{
    int32_t spi_rt;
    
    unsigned char txData[32] = {0};
    unsigned char rxData[32] = {0};
    
    txData[0] = FRAM_RDID;
    spi_rt = send_cmd(txData, rxData, len+1);

    memcpy(id, rxData+1, len);
    
    return spi_rt;
}

int MB85RS_Init(int bus, int select)
{
    if(!g_pFRAM)
        g_pFRAM = (MB85RS_t *)malloc(sizeof(MB85RS_t));

    if(g_pFRAM){
        g_pFRAM->bus = bus;
        g_pFRAM->select = select;
    }else{
        return -1;
    }
    
    uint8_t chipId[9] = {0};
    int32_t spi_rt = MB85RS_RDID(chipId, sizeof(chipId));
    if(spi_rt < 0)
        return spi_rt;

    printf("chip Id: ");
    for(int i = 0; i < 9; i++){
        printf("%02x ", chipId[i]);
    }
    printf("\n");
    
    if(chipId[0] == 0x04) {
        /* 富士通 */
        if((chipId[2] & 0x1f) == 0x07){
            g_AddrBytes3 = 1;
            g_Density = 128 * 1024;
        } else if((chipId[2] & 0x1f) == 0x05) {
            g_AddrBytes3 = 0;
            g_Density = 32 * 1024;
        } else {
            g_AddrBytes3 = 0;
            g_Density = 0;
            return FRAM_ERR;
        }
        
    } else if(chipId[6] == 0xC2) {
        /* FM */
        if((chipId[7] & 0x1f) == 0x04) {
            g_AddrBytes3 = 1;
            g_Density = 128 * 1024;
        } else if((chipId[7] & 0x1f) == 0x02) {
            g_AddrBytes3 = 0;
            g_Density = 32 * 1024;
        } else {
            g_AddrBytes3 = 0;
            g_Density = 0;
            return FRAM_ERR;
        }
        
    } else {
        g_AddrBytes3 = 0;
        g_Density = 0;
        return FRAM_ERR;
    }    

    return FRAM_OK;
}


