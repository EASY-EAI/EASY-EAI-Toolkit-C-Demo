#ifndef     IIC_H
#define    IIC_H

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C"{
#endif

extern int32_t iic_init(const char  *path);
extern bool iic_release(int32_t mfd);
extern bool iic_set_addr_len(int32_t mfd,int32_t len);
extern bool iic_set_addr(int32_t mfd,int32_t addr);
extern bool iic_read(int32_t mfd ,unsigned short addr, uint8_t* buf , int32_t read_len);
extern bool iic_write(int32_t mfd,unsigned short addr,uint8_t *buf,int32_t write_len);


#if defined(__cplusplus)
}
#endif


#endif

