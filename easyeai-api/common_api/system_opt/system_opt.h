 /**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: Jiehao.Zhong <zhongjiehao@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef SYSTEM_OPT_H
#define SYSTEM_OPT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif
//system resource view api
typedef struct cpu_occupy_ //定义一个cpu occupy的结构体
{
    char name[20];
    uint32_t user;
    uint32_t nice;
    uint32_t system;
    uint32_t idle;
    uint32_t iowait;
    uint32_t irq;
    uint32_t softirq;
}cpu_occupy_t;
extern double cpu_tempture();
extern double npu_tempture();
extern void   get_cpu_occupy(cpu_occupy_t *cpust);
extern double cal_cpu_occupy(cpu_occupy_t *o, cpu_occupy_t *n);
extern double memory_usage();
extern double partition_usage(const char *path);

//system time parameter config api
// be used for debug
extern uint64_t get_timeval_us();
extern uint64_t get_timeval_ms();
extern uint64_t get_timeval_s();
// be used for delay
extern uint32_t osTask_usDelay(uint32_t us);
extern uint32_t osTask_msDelay(uint32_t ms);
extern uint32_t osTask_sDelay(uint32_t s);
extern uint32_t msleep (uint32_t ms);
// be used for normal
extern int32_t get_time_stamp();
extern void get_system_date_time(uint32_t *curDate, uint32_t *curTime);
extern void set_system_date_time(int year, int mon, int day, int hour, int min, int second);
extern uint8_t calc_week_day(int y,int m, int d);

//process & thread operation
// thread
typedef	void *(*ThreadEntryPtrType)(void *);
extern int32_t CreateNormalThread(ThreadEntryPtrType entry, void *para, pthread_t *pid);
extern int32_t CreateJoinThread(ThreadEntryPtrType entry, void *para, pthread_t *pid);
extern int32_t WaitExitThread(pthread_t pid);
// process
extern int32_t exec_cmd_by_system(const char *cmd);
extern int32_t exec_cmd_by_popen(const char *cmd, char *result);

#if defined(__cplusplus)
}
#endif
#endif // SYSTEM_OPT_H