#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "system_opt.h"

#define CLITNE_ID_BASE   1000
#define SERVER_CLI_ID  (CLITNE_ID_BASE+1)
#define CLIENT_CLI_ID  (CLITNE_ID_BASE+2)

enum MsgType{//信息描述标志
    MSGTYPE_NULL = 0,
    MSGTYPE_CLIENT_DATA,
    MSGTYPE_CLIENT_UPGRADE,
};

typedef struct{
    int data_a;
    int data_b;
    int data_c;
} Data_t;

static void waittingTargetClientReady(int32_t cliId)
{
    while(1){
        IPC_client_query_registered_client(cliId);
        if(IPC_client_dstClient_is_registered())
            break;
        usleep(200*1000);
    }
    return ;
}

int serverHanndle(void *pObj, IPC_MSG_t *pMsg)
{
    Data_t *pData = (Data_t *)pObj;
    if(MSGTYPE_CLIENT_DATA == pMsg->msgType)
    {
        printf("***********客户端收到数据：a:%d , b:%d , c:%d*************\n",pData->data_a, pData->data_b , pData->data_c);
    }else if(MSGTYPE_CLIENT_UPGRADE == pMsg->msgType){

    }
    return 0;
}

int main()
{
    /*新建CLIENT_CLI_ID客户端*/
    IPC_client_create();
    int ret = IPC_client_init(CLIENT_CLI_ID);
    if(-1 == ret) {
        printf("IPCServer_client Create faild !!!\n");
        return -1;
    }
    Data_t *pData = (Data_t *)malloc(sizeof(Data_t));
    memset(pData, 0, sizeof(Data_t));
    IPC_client_set_callback(pData/*这个指针会传到clientHanndle的pObj*/, serverHanndle);
    printf("初始化成功！\n");

    // /*等待服务端的SERVER_CLI_ID客户端注册成功*/
    // waittingTargetClientReady(SERVER_CLI_ID);
    // /*循环向SERVER_CLI_ID发送信息*/
    while (1)
    {
        sleep(2);   
        pData->data_a += 1;
        pData->data_b += 10;
        pData->data_c += 100;
        ret = IPC_client_sendData(SERVER_CLI_ID, MSGTYPE_CLIENT_DATA, &pData, sizeof(Data_t));
        if(-1 == ret)
        {
            printf(" IPC_client_sendData faild !!!\n");    
            goto exit;
        }   
    }
exit:
    return 0;
}

