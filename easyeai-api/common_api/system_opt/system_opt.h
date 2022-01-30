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
#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif

//network parameter config api
extern int set_net_ipv4(const char *ip, const char *mask, const char *gateway);

extern int get_local_Ip(const char *device, char *ip, int ip_len);
extern int get_local_Mac(const char *device, char *mac, int mac_len);

extern bool ipv4_str_to_bin(char *strIP, char *binIP);
extern bool mac_str_to_bin(char *strMac, char *binMac);

extern bool compare_IpAddr(char *addr1, char *addr2);

extern char* netAddrToStr(uint64_t netAddr);
extern uint64_t strToNetAddr(char *p_str);

//system time parameter config api
extern uint64_t get_timeval_us();
extern uint64_t get_timeval_ms();
extern uint64_t get_timeval_s();

extern int get_time_stamp();
extern void get_system_date_time(uint32_t *curDate, uint32_t *curTime);
extern void set_system_date_time(int year, int mon, int day, int hour, int min, int second);

//thread operation
typedef	void *(*ThreadEntryPtrType)(void *);
extern int CreateNormalThread(ThreadEntryPtrType entry, void *para, pthread_t *pid);


#if defined(__cplusplus)
}
#endif
#endif // SYSTEM_OPT_H