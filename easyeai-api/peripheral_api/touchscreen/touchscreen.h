#ifndef   TOUCHSCREEN_H
#define  TOUCHSCREEN_H


#include <stdbool.h>
#include <stdint.h>


#if defined(__cplusplus)
extern "C"{
#endif




#define TS_PRESS       (0x1<<0) // 按下屏幕
#define TS_RELEASE     (0x1<<1) // 松开屏幕
#define TS_CLICK       (0x1<<2) // 单击屏幕
#define TS_DOUBLECLICK (0x1<<3) // 双击屏幕
#define TS_LONGPRESS   (0x1<<4) // 长按屏幕
#define TS_DRAG   (0x1<<5) // 拖动屏幕


typedef int (*TsHandle)(uint32_t event, int x , int y);




extern int   Init_TsEven(const char* dev_name,int nonblock);
extern int set_even_handle(TsHandle handle);

#if defined(__cplusplus)
}
#endif


#endif 







