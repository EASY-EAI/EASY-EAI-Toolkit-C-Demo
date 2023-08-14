/**
 *
 * Copyright 2023 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: ZJH <zhongjiehao@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef GPIO_H
#define GPIO_H

#include <sys/types.h>
 
#include <stdint.h>
#include <stdbool.h>

#define DIR_OUTPUT 1
#define DIR_INPUT  0

typedef struct {
    char pinName[32];
    int  direction;
    int  val;
}GPIOCfg_t;

#if defined(__cplusplus)
extern "C"{
#endif

extern int pin_out_val(const char *pinName, int val);
extern int read_pin_val(const char *pinName);
extern int gpio_init(const GPIOCfg_t uartCfgs[], int arraySize);
extern int gpio_uinit();


#if defined(__cplusplus)
}
#endif

#endif