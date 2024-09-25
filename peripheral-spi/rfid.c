#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "spiapi.h"
#include "rc522.h"

#define MI_READ 0x01
#define MI_WRITE 0x02
#define MI_GET_ID 0x04

//spi_mode 定义
static int dev_spi_bus = 0;
static int dev_spi_select = 0;
static unsigned char mode;
static unsigned char addr = 4;
static unsigned char flag = 0;
static unsigned char bits = 8;
static unsigned int speed = 100000;
static uint16_t delay = 0;

unsigned char card_rev_buf[16]  = { 0 };
    /* 
    *扇区密码:A，扇区数:16，每个扇区
    *密码字节数:16Byte
    */
    unsigned char sector_key_a[16][16];
    unsigned char data_buf[16] = 
    {0x01, 0x02, 0x03, 0x04, 
     0x05, 0x06, 0x07, 0x08, 
     0x09, 0x0A, 0x0B, 0x0C, 
     0x0D, 0x0E, 0x0F, 0x10};

void print_buff(unsigned char* data_buf, int len) {    
    int i = 0;
    for(i = 0; i < len; i++){
	printf("%02x", data_buf[i]);
    }
    printf("\n");
}

void analyze(unsigned char * buf, int len, char * data) {
    char* ptrData ;
    char* endPtr ;
    int itteration = 0;
    ptrData = data;
    while (ptrData) {
	if (itteration < len) {
    	    buf[itteration++]  = (unsigned char)strtoul(ptrData, &endPtr, 16);
	}
	if (*endPtr) ptrData = endPtr; else ptrData = NULL;
    }
}


/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int main (int argc, char **argv) {
    memset(data_buf, 0x00, sizeof data_buf);
    int status		= MI_ERR;
    int numAtempt	= 1;
    int fd   = spi_init(dev_spi_bus, dev_spi_select, mode, bits,  speed,  delay);
	rfid_init(dev_spi_bus ,dev_spi_select , fd);   
    flag = MI_GET_ID;

    while(1)
    {
            /*
            *在天线的区域寻找卡片，
            *没有进入休眠状态..
            *返回卡类型，2个字节。
            */
            while(rfid_request(PICC_REQIDL, &card_rev_buf[0]) != MI_OK && numAtempt-- >= 0) {
                usleep(500);
            }
            /*
            *防碰撞，返回卡号，
            * 4字节。
            */
            if(rfid_anticoll(&card_rev_buf[2]) == MI_OK) {
            
                status = rfid_select(&card_rev_buf[2]);
                if(status != MI_ERR) {
                    if(flag == MI_GET_ID) {
                    /*
                    * 打印卡id。
                    */
                    //printf("Card ID: 0x%02x, 0x%02x\n", card_rev_buf[0], card_rev_buf[1]);
                    printf("Card ID:%02x%02x%02x%02x\n", card_rev_buf[2], card_rev_buf[3],	card_rev_buf[4], card_rev_buf[5]);
                    } else if (flag == MI_READ) {
                    memset(sector_key_a, 0xff, 256);
                    memset(data_buf, 0x00, sizeof data_buf);
                    status = rfid_auth_state(PICC_AUTHENT1A, addr, sector_key_a[addr/4], &card_rev_buf[2]);
                        if(status == MI_OK) {
                            status = rfid_read(addr, data_buf);
                            if(status == MI_OK) {
                                print_buff(data_buf, 16);
                        /*for(i = 0; i < 16; i++){
                                    printf("%02x ", data_buf[i]);
                                }
                                printf("\n");
                        */
                            }
                        } else {
                            printf("Error reading");
                            close(fd);
                            exit(1);
                        }
                    } else if (flag == MI_WRITE) {
                    memset(sector_key_a, 0xff, 256);
                        if(addr == 0 || addr % 4 == 3) {
                            close(fd);
                            exit(1);
                    }
                    status = rfid_auth_state(PICC_AUTHENT1A, addr,  sector_key_a[addr/4], &card_rev_buf[2]);
                        if(status == MI_OK) {
                        status = rfid_write(addr, data_buf);
                            if(status != MI_OK) {
                                printf("rfid write failure!\n");
                                close(fd);
                                exit(1);
                            }    
                    } else {
                        printf("Error writing");
                        close(fd);
                        exit(1);
                    }
                    } else {
                        printf("Not implemented\n");
                    }
                    status = rfid_halt();
                    if(status != MI_OK)  {
                        //printf ("rfid halt failure! [ERROR %d]\n", status);
                    }
                    } else {
                        // printf("None\n");
                     }
                } else {
                        // printf("None\n");
                }
    }
    
    spi_exit(dev_spi_bus , dev_spi_select);
    return 0;
} /* ----- End of main() ----- */
