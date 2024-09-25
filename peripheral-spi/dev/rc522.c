#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <linux/types.h>

#include "rc522.h"
#include <spiapi.h>



int fd;
int spi_bus;
int spi_select;


/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void pabort(const char *str)
{
    perror(str);
    abort();
} /* ----- End of paboart()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
static void get_cur_time (unsigned long long *usec)
{
    struct timeval tm;

    gettimeofday(&tm, NULL);

    *usec = (unsigned long long)tm.tv_sec * 1000000 +
        (unsigned long long)tm.tv_usec;
} /* ----- End of get_cur_time()  ----- */




/**************************************************************************************
 *  Description:读寄存器值
 *   Input Args:   addr：寄存器地址    *data：传出参数（寄存器数据）
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void read_reg(unsigned char addr, unsigned char *data)
{
    int status      = MI_ERR;

    addr = ((addr << 1) & 0x7E) | 0x80;
    memset(data, 0, sizeof(unsigned char));

    // status = write(fd, &addr, 1);
    status = spi_transfer(spi_bus, spi_select, &addr, NULL, 1);
    if(status < 0)
    {
        pabort("can't write byte to device");
    }

    // status = read(fd, data, 1);
    status = spi_transfer(spi_bus, spi_select, NULL,  data, 1);
    if(status < 0)
    {
        pabort("can't read byte form device");
    }
} /* ----- End of read_reg()  ----- */



/**************************************************************************************
 *  Description: 写寄存器值
 *   Input Args: addr：写入寄存器的地址      data:写入的数据
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void write_reg(unsigned char addr, unsigned char data)
{
    unsigned char val[2];
    unsigned char rx_buf[50];
    int status;
    memset(rx_buf, 0 , (int )(sizeof(rx_buf) / sizeof(rx_buf[0])));
    addr = ((addr << 1) & 0x7E);
    val[0] = addr;
    val[1] = data;
    // status = write(fd, val, 2);
    status = spi_transfer(spi_bus, spi_select, val, rx_buf, 2);
    if(status < 0)
    {
        pabort("can't write byte to device");
    }
} /* ----- End of write_reg()  ----- */



/**************************************************************************************
 *  Description: 写入字符串
 *   Input Args: addr ： 写入的寄存器     *data：字符串首地址    len:字符串长度
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void write_string(unsigned char addr, unsigned char *data, unsigned char len)
{
    int i  = 0;
    unsigned char val[len + 1];
    
    int status;
    
    addr = ((addr << 1) & 0x7E);
    val[0] = addr;
    for(i = 0; i < len; i++)
    {
        val[i + 1] = data[i];
    }
    
    // status = write(fd, val, len + 1);
    status = spi_transfer(spi_bus, spi_select, val, NULL, len + 1);
    if(status < 0)
    {
        pabort("write string");
    }

} /* ----- End of write_string()  ----- */

/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void clear_bit_mask (unsigned char reg, unsigned char mask)
{
    unsigned char tmp = 0x00;

    read_reg(reg, &tmp);
    write_reg(reg, tmp & ~mask);
} /* ----- End of clear_bit_mask()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void set_bit_mask (unsigned char reg, unsigned char mask)
{
    unsigned char tmp = 0x00;
    read_reg(reg, &tmp);
    write_reg(reg, tmp | mask);
} /* ----- End of set_bit_mask()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void calulatate_crc (unsigned char *indata, unsigned char len, unsigned char *outdata)
{
    unsigned char reg_val   = 0;
    unsigned long long cur_usec,last_usec;

    clear_bit_mask(DIV_IRQ_REG, 0x04);
    write_reg(COMMAND_REG, PCD_IDLE);
    set_bit_mask(FIFO_LEVEL_REG, 0x80);

    write_string(FIFO_DATA_REG, indata, len);

    write_reg(COMMAND_REG, PCD_CALCCRC);

    get_cur_time(&last_usec);
    do
    {
        read_reg(DIV_IRQ_REG, &reg_val);
        get_cur_time(&cur_usec);
    }
    while (!(last_usec + 25000 < cur_usec) && !(reg_val & 0x04));

    read_reg(CRC_RESULT_REG_L, &outdata[0]);
    read_reg(CRC_RESULT_REG_M, &outdata[1]);
} /* ----- End of calulatate_crc()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_com (unsigned char command, unsigned char *indata,
        unsigned char inlenbyte, unsigned char *outdata,
        unsigned int  *outlenbit)
{
    int           status        = MI_ERR;
    unsigned char irq_en        = 0x00;
    unsigned char wait_for      = 0x00;
    unsigned char last_bits     = 0x00;
    unsigned char reg_val       = 0x00;
    unsigned char com_irq_reg   = 0x00;
    unsigned int  i;
    unsigned long long cur_usec,last_usec;

    switch(command)
    {
        case PCD_AUTHENT:
            irq_en      = 0x12;
            wait_for    = 0x10;
            break;
        case PCD_TRANSCEIVE:
            irq_en      = 0x77;
            wait_for    = 0x30;
            break;
        default:
            break;
    }

    write_reg(COM_IEN_REG, irq_en | 0x80);
    clear_bit_mask(COM_IRQ_REG, 0x80);
    write_reg(COMMAND_REG, PCD_IDLE);
    set_bit_mask(FIFO_LEVEL_REG, 0x80);


    write_string(FIFO_DATA_REG, indata, inlenbyte);
    
    /* 执行命令 */
    write_reg(COMMAND_REG, command);
    if(command == PCD_TRANSCEIVE)
    {
        set_bit_mask(BIT_FRAMING_REG, 0x80);
    }

    get_cur_time(&last_usec);
    do
    {
        read_reg(COM_IRQ_REG, &com_irq_reg);
        get_cur_time(&cur_usec);
    }
    while(!(last_usec + 25000 < cur_usec) && !(com_irq_reg & 0x01) 
            && !(com_irq_reg & wait_for));

    clear_bit_mask(BIT_FRAMING_REG, 0x80);

    if(!(last_usec + 25000 < cur_usec))
    {
        read_reg(ERROR_REG, &reg_val);
        if(!(reg_val & 0x1B))
        {
            status = MI_OK;
            if(com_irq_reg & irq_en & 0x01)
            {
                status = MI_NOTAGERR; 
            }

            if(command == PCD_TRANSCEIVE)
            {
                    read_reg(FIFO_LEVEL_REG, &reg_val);
                    read_reg(CONTROL_REG, &last_bits);
                    last_bits = last_bits & 0x07;
                    if(last_bits)
                    {
                        *outlenbit = (reg_val - 1) * 8 + last_bits;
                    }
                    else
                    {
                        *outlenbit = reg_val * 8;
                    }

                    if(0 == reg_val)
                    {
                        reg_val = 1;
                    }

                    if(reg_val > MAXRLEN)
                    {
                        reg_val = MAXRLEN;
                    }

                    for(i = 0; i < reg_val; i++)
                    {
                        read_reg(FIFO_DATA_REG, &outdata[i]);
                    }
            }
        }
        else
        {
            status = MI_ERR;
        }
    }

    set_bit_mask(CONTROL_REG, 0x80);
    write_reg(COMMAND_REG, PCD_IDLE);

    return status;
} /* ----- End of rfid_com()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_request (unsigned char reg_code, unsigned char *card_type)
{
    int status;
    unsigned int len_bit;
    unsigned char com_buf[MAXRLEN];

    clear_bit_mask(STATUS2_REG, 0x08);
    write_reg(BIT_FRAMING_REG, 0x07);
    set_bit_mask(TX_CONTROL_REG, 0x03);

    com_buf[0] = reg_code;

    status = rfid_com(PCD_TRANSCEIVE, com_buf, 1, com_buf, &len_bit);

    if((status == MI_OK) && (len_bit == 0x10))
    {
        *card_type = com_buf[0];
        *(card_type + 1) = com_buf[1]; 
    }
    else
    {
        status = MI_ERR;
    }

    return status;
} /* ----- End of rfid_request()  ----- */



/**************************************************************************************
 *  Description:卡片防冲撞
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_anticoll (unsigned char *sernum)
{
    int           status       = 0;
    unsigned char i            = 0;
    unsigned char sernum_check = 0;
    unsigned int  len;
    unsigned char com_buf[MAXRLEN];

    clear_bit_mask(STATUS2_REG, 0x08);
    write_reg(BIT_FRAMING_REG, 0x00);
    clear_bit_mask(COLL_REG, 0x80);

    com_buf[0] = PICC_ANTICOLL1;
    com_buf[1] = 0x20;

    status = rfid_com(PCD_TRANSCEIVE, com_buf, 2, com_buf, &len);
    if(status == MI_OK)
    {
        for(i = 0; i < 4; i++)
        {
            *(sernum + i) = com_buf[i];
            sernum_check ^= com_buf[i];
        }

        if(sernum_check != com_buf[i])
        {
            status = MI_ERR;
        }
    }

    set_bit_mask(COLL_REG, 0x80);

    return status;
} /* ----- End of rfid_anticoll()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_select (unsigned char *sernum)
{
    int             status = 0;
    unsigned char   i; 
    unsigned int    len_bit;
    unsigned char   com_buf[MAXRLEN];

    com_buf[0] = PICC_ANTICOLL1;
    com_buf[1] = 0x70;
    com_buf[6] = 0;

    for(i = 0; i < 4; i++)
    {
        com_buf[i + 2]  = *(sernum + i);
        com_buf[6]     ^= *(sernum + i);
    }

    calulatate_crc(com_buf, 7, &com_buf[7]);

    clear_bit_mask(STATUS2_REG, 0x08);

    status = rfid_com(PCD_TRANSCEIVE, com_buf, 9, com_buf, &len_bit);

    if((status == MI_OK) && (len_bit == 0x18))
    {
        status = (int)com_buf[0];
    }
    else
    {
        status =MI_ERR;
    }

    return status;
} /* ----- End of rfid_select()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_auth_state (unsigned char auth_mode, unsigned char addr, 
        unsigned char *key, unsigned char *sernum)
{
    int             status      = 0;
    unsigned int    len_bit     = 0;
    unsigned char   reg_val     = 0;
    unsigned char   com_buf[MAXRLEN];

    /* 验证指令 + 块地址 + 扇区密码 + 卡序列号 */
    com_buf[0] = auth_mode;
    com_buf[1] = addr;

    memcpy(&com_buf[2], key, 6);
    memcpy(&com_buf[8], sernum, 6);

    status = rfid_com(PCD_AUTHENT, com_buf, 12, com_buf, &len_bit);
    read_reg(STATUS2_REG, &reg_val);
    if((status != MI_OK) || (!(reg_val & 0x08)))
    {
        status = MI_ERR;
    }

    return status;
} /* ----- End of rfid_auth_state()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_read (unsigned char addr, unsigned char *data)
{
    int             status      = 0;
    unsigned int    len_bit     = 0;
    unsigned char   com_buf[MAXRLEN];

    com_buf[0] = PICC_READ;
    com_buf[1] = addr;

    calulatate_crc(com_buf, 2, &com_buf[2]);

    status = rfid_com(PCD_TRANSCEIVE, com_buf, 4, com_buf, &len_bit);
    if((status == MI_OK) && (len_bit == 0x90))
    {
        memcpy(data, com_buf, 16);
    }
    else
    {
        status = MI_ERR;
    }

    return status;
} /* ----- End of rfid_read()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_write (unsigned char addr, unsigned char *data)
{
    int             status      = 0;
    unsigned int    len_bit     = 0;
    unsigned char   com_buf[MAXRLEN];

    com_buf[0] = PICC_WRITE;
    com_buf[1] = addr;
    calulatate_crc(com_buf, 2, &com_buf[2]);

    status = rfid_com(PCD_TRANSCEIVE, com_buf, 4, com_buf, &len_bit);

    if((status == MI_OK) && (len_bit == 4) && ((com_buf[0] & 0x0F) == 0x0A))
    {
        /* 向FIFO写16Byte数据 */
        memcpy(com_buf, data, 16);
        calulatate_crc(com_buf, 16, &com_buf[16]);

        status = rfid_com(PCD_TRANSCEIVE, com_buf, MAXRLEN, com_buf, &len_bit);
        /* 
         * 也许这个地方有个bug，但是不管怎么样可以写IC卡的块。
         * 原来这里是：
         * if((status != MI_OK) || (len_bit != 4) || ((com_buf[0] & 0x0F) != 0x0A))
         */
        if((status != MI_OK))
        {
            status = MI_ERR;
        }
    }

    return status;
} /* ----- End of rfid_write()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_halt (void)
{
    int             status      = 0;
    unsigned int    len_bit     = 0;
    unsigned char   com_buf[MAXRLEN];

    com_buf[0] = PICC_HALT;
    com_buf[1] = 0;

    calulatate_crc(com_buf, 2, &com_buf[2]);

    status = rfid_com(PCD_TRANSCEIVE, com_buf, 4, com_buf, &len_bit);
    //printf("HLT status: %d\n", status);
    status = MI_OK;
    return status;
} /* ----- End of rfid_halt()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void rfid_reset (void)
{

    write_reg(COMMAND_REG, PCD_RESETPHASE);
    usleep(10);

    write_reg(MODE_REG, 0x3D);
    write_reg(T_RELOAD_REG_L, 30);
    write_reg(T_RELOAD_REG_H, 0);
    write_reg(T_MODE_REG, 0x8D);
    write_reg(T_PRESCALER_REG, 0x3E);

    write_reg(TX_AUTO_REG, 0x40);

} /* ----- End of rfid_reset()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void rfid_antenna_on (void)
{
    unsigned char reg_val = 0;

    read_reg(TX_CONTROL_REG, &reg_val);
    if(!(reg_val & 0x03))
    {
        set_bit_mask(TX_CONTROL_REG, 0x03);
    }
} /* ----- End of rfid_antenna_on()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void rfid_antenna_off (void)
{
    clear_bit_mask(TX_CONTROL_REG, 0x03);
} /* ----- End of rfid_antenna_off()  ----- */




/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
int rfid_conf_iso_type (unsigned char type)
{
    if(type == 'A')
    {
        clear_bit_mask(STATUS2_REG, 0X08);
        write_reg(MODE_REG, 0x3D);
        write_reg(RX_SEL_REG, 0x86);
        write_reg(RF_CFG_REG, 0x7f);
        write_reg(T_RELOAD_REG_L, 30);
        write_reg(T_RELOAD_REG_H, 0);
        write_reg(T_MODE_REG, 0x8D);
        write_reg(T_PRESCALER_REG, 0x3E);
        usleep(10);
        rfid_antenna_on();
    }
    else
    {
        return MI_ERR;
    }

    return MI_OK;
} /* ----- End of rfid_conf_iso_type()  ----- */



/**************************************************************************************
 *  Description:
 *   Input Args:
 *  Output Args:
 * Return Value:
 *************************************************************************************/
void rfid_init (int rfid_bus, int rfid_select,int rfid_fd)
{
    int ret;
    spi_bus = rfid_bus;
    spi_select = rfid_select;
    rfid_reset();
    rfid_antenna_off();
    rfid_antenna_on();
    ret = rfid_conf_iso_type('A');
    if(MI_OK != ret)
    {
        pabort("can't config iso type");
    }
} /* ----- End of rfid_init()  ----- */

