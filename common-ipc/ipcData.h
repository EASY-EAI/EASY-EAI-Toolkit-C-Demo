#ifndef __IPCDATA_H__
#define __IPCDATA_H__

#include <stdint.h>

#define CLITNE_ID_BASE   1000
#define A_CLI_ID  (CLITNE_ID_BASE+1)
#define B_CLI_ID  (CLITNE_ID_BASE+2)

typedef struct{
    int a;
    int b;
    int c;
} Data_t;

typedef struct{
    int a;
    int b;
    int c;
} UPGRADE_t;

enum MsgType{//信息描述标志
    MSGTYPE_NULL = 0,
    MSGTYPE_CLIENT_DATA,
    MSGTYPE_UPGRADE,
    MSGTYPE_NUM
};

#endif // __IPCDATA_H__