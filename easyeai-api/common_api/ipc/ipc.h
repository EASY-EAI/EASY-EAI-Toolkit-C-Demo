 /**
 *
 * Copyright 2023 by Guangzhou Easy EAI Technologny Co.,Ltd.
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

#ifndef IPC_H
#define IPC_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#if defined(__cplusplus)
extern "C" {
#endif
// IPC
#define IPCSERVER_PORT 7000 //IPC服务器占用端口(注意：此值仅用于开发参考，不可以对其进行修改)
typedef struct {
    char msgHeader[8];
    int32_t srcClientId;
    int32_t dstClientId;
    int32_t msgType;
    int32_t msgLen;
    void *payload;
}IPC_MSG_t;
typedef	int32_t (*IPC_Client_CB)(void *, IPC_MSG_t *);

extern int32_t IPC_server_create(int clientMaxNum);
extern int32_t IPC_client_create();
extern int32_t IPC_client_init(int32_t cliId);
extern int32_t IPC_client_unInit();
extern int32_t IPC_client_set_callback(void *pObj, IPC_Client_CB func);
extern int32_t IPC_client_query_registered_client(int32_t dstCliId);
extern int32_t IPC_client_dstClient_is_registered();
extern int32_t IPC_client_sendData(int32_t tagId, int32_t type, void *data, int32_t dataLen);

#if defined(__cplusplus)
}
#endif
#endif // IPC_H