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

//network parameter config api
extern int32_t set_net_ipv4(const char *ip, const char *mask, const char *gateway);

extern int32_t get_local_Ip(const char *device, char *ip, int ip_len);
extern int32_t get_local_Mac(const char *device, char *mac, int mac_len);

extern bool ipv4_str_to_bin(char *strIP, char *binIP);
extern bool mac_str_to_bin(char *strMac, char *binMac);

extern bool compare_IpAddr(char *addr1, char *addr2);

extern char* netAddrToStr(uint64_t netAddr);
extern uint64_t strToNetAddr(char *p_str);

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
// process
extern int32_t exec_cmd_by_system(const char *cmd);
extern int32_t exec_cmd_by_popen(const char *cmd, char *result);
// IPC
typedef struct {
    char msgHeader[8];
    int32_t srcClientId;
    int32_t dstClientId;
    int32_t msgType;
    int32_t msgLen;
    void *payload;
}IPC_MSG_t;
typedef	int32_t (*IPC_Client_CB)(void *, IPC_MSG_t *);

extern int32_t IPC_server_create(int port, int clientMaxNum);
extern int32_t IPC_client_create();
extern int32_t IPC_client_init(int32_t srvPort, int32_t cliId);
extern int32_t IPC_client_unInit();
extern int32_t IPC_client_set_callback(void *pObj, IPC_Client_CB func);
extern int32_t IPC_client_sendData(int32_t tagId, int32_t type, void *data, int32_t dataLen);

#if defined(__cplusplus)
}
#endif
#endif // SYSTEM_OPT_H