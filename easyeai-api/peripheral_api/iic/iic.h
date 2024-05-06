#ifndef IIC_H
#define IIC_H

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C"{
#endif

extern int32_t iic_init(const char  *path);
extern    void iic_release(int32_t fd);
extern int32_t iic_set_addr_len(int32_t fd, int32_t addrbits);
extern int32_t iic_set_addr(int32_t fd, int32_t addr);
extern int32_t iic_read(int32_t fd, unsigned short addr, uint8_t *pBuf, int32_t read_len);
extern int32_t iic_write(int32_t fd, unsigned short addr, uint8_t *pBuf, int32_t write_len);


#if defined(__cplusplus)
}
#endif


#endif

