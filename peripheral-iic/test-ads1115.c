#include <stdio.h>
#include <unistd.h>

#include "iic.h"
#include "ads1115.h"

static int32_t ads1115_config_register(uint32_t mfd, uint8_t pointADD,uint8_t configH,uint8_t configL)
{
    uint8_t reg_data[3] = {pointADD, configH, configL};
    int32_t ret = iic_write(mfd, ADS1115_ADDRESS, reg_data, 3);

    if(ret)
        return 0;
    else
        return -1;
}

static int16_t ads1115_read_data(uint32_t mfd)
{
    int32_t ret = false;
    /*读取数据*/
    uint8_t tx_data[1];
    tx_data[0] = ADS1015_REG_POINTER_CONVERT;
    ret = iic_write(mfd, ADS1115_ADDRESS, tx_data,1);
    if(!ret){
        printf("iic write faild !\n");
    }

    uint8_t rx_data[3]={0};
    ret = iic_read(mfd, ADS1115_ADDRESS, rx_data,2);
    if(!ret){
        printf("iic read faild !\n");
    }

    int16_t data = 0;
    data=rx_data[0]*256+rx_data[1];
    return data;
}

static double ads1115_get_voltage_val(uint32_t mfd, uint8_t pointADD,uint8_t configH,uint8_t configL)
{
    double val;
    int16_t ad_val;
    
    /*配置寄存器*/
    ads1115_config_register(mfd,pointADD,configH,configL);
    usleep(10 * 1000);
    
    ad_val=ads1115_read_data(mfd);
    if((ad_val==0x7FFF)|(ad_val==0X8000)) {//是否超量程了
        ad_val=0;
        printf("over PGA\r\n");
    }

    switch((0x0E&configH)>>1)//量程对应的分辨率
    {
        case(0x00):
            val=(double)ad_val*187.5/1000000.0;//
        break;
        case(0x01):
            val=(double)ad_val*125/1000000.0;
        break;
        case(0x02):
            val=(double)ad_val*62.5/1000000.0;
        break;
        case(0x03):
            val=(double)ad_val*31.25/1000000.0;
        break;
        case(0x04):
            val=(double)ad_val*15.625/1000000.0;
        break;
        case(0x05):
            val=(double)ad_val*7.8125/1000000.0;
        break;
    }
    
    return val;
}

int main(int argc, char const *argv[])
{
    double val;
    int fd = iic_init("/dev/i2c-5");
    if(fd < 0){
        printf("iic init faild \n");
        return -1;
    }
    
    if(0 != iic_set_addr_len(fd, 7)){
        return -1;
    }
    
    if(0 != iic_set_addr(fd, ADS1115_ADDRESS)){
        return -1;
    }    
    
    while (1) {
        val = ads1115_get_voltage_val(fd,ADS1015_REG_POINTER_CONFIG,CONFIG_REG_H,CONFIG_REG_L);
        printf("val: %f V\r\n",val);
        sleep(1);
    }
    
    iic_release(fd);
    return 0;
}

