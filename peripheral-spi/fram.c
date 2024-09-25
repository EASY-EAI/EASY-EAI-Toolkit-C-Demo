#include <stdio.h>

#include <sys/ioctl.h>

#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "spiapi.h"
#include "mb85rs64.h"

#define SPI0_BUS 0
#define SPI1_BUS 1
#define CS0n 0
#define CS1n 1
/*
---------<linux/spi/spidev.h>--------
#define SPI_CPHA 0x01
#define SPI_CPOL 0x02
#define SPI_MODE_0 (0|0)
#define SPI_MODE_1 (0|SPI_CPHA)
#define SPI_MODE_2 (SPI_CPOL|0)
#define SPI_MODE_3 (SPI_CPOL|SPI_CPHA)
#define SPI_CS_HIGH   0x04
#define SPI_LSB_FIRST 0x08
#define SPI_3WIRE     0x10
#define SPI_LOOP      0x20
#define SPI_NO_CS     0x40
#define SPI_READY     0x80
#define SPI_TX_DUAL   0x100
#define SPI_TX_QUAL   0x200
#define SPI_RX_DUAL   0x400
#define SPI_RX_QUAL   0x800
-------------------------------------
*/
#define SPI_MODE SPI_MODE_0
#define SPI_BITS 8
#define SPI_SPEED 100000
#define SPI_DELAY 0


/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int main (int argc, char **argv)
{
    int ret = spi_init(SPI0_BUS, CS0n, SPI_MODE, SPI_BITS, SPI_SPEED, SPI_DELAY);
    if(ret) {
        printf("SPI init faild !\n");
        return -1;
    }

	ret = MB85RS_Init(SPI0_BUS, CS0n);
    if(ret){
        printf("MB85RS init faild !\n");
        return -1;
    }

    unsigned char buf[8] = {0};
    /// ====================>> Read ====================>>
    ret = MB85RS_Read(0x4, buf, sizeof(buf));
    if(ret){
        printf("--%d-- MB85RS Read faild !\n", ret);
        return -1;
    }
    printf("Read Data: ");
    for(int i = 0; i < 8; i++){
        printf("%02x ", buf[i]);
    }
    printf("\n");
    
    /// ====================>> Write ====================>>
    buf[0] = 0x11;
    buf[1] = 0x22;
    buf[2] = 0x33;
    buf[3] = 0x44;
    buf[4] = 0x55;
    buf[5] = 0x66;
    buf[6] = 0x77;
    buf[7] = 0x88;
    ret = MB85RS_Write(0x4, buf, sizeof(buf));
    if(ret){
        printf("--%d-- MB85RS Write faild !\n", ret);
        return -1;
    }
    
    /// =================>> Read Again ==================>>
    ret = MB85RS_Read(0x4, buf, sizeof(buf));
    if(ret){
        printf("--%d-- MB85RS Read Again faild !\n", ret);
        return -1;
    }
    printf("Read Data: ");
    for(int i = 0; i < 8; i++){
        printf("%02x ", buf[i]);
    }
    printf("\n");

    return 0;
} /* ----- End of main() ----- */
