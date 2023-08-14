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

#ifndef UART_H
#define UART_H

#include <sys/types.h>
 
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
extern "C"{
#endif

extern int  UART_Open(const char *port);
extern void UART_Close(int fd);
extern int  UART_Set(int fd, int speed, int flow_ctrl, int databits, int stopbits, int parity);
extern int  UART_Recv(int fd, char *rcv_buf, int data_len);
extern int  UART_Send(int fd, char *send_buf,int data_len);

#if defined(__cplusplus)
}
#endif

#endif




