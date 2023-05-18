#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "ipcData.h"

#include "ipc.h"

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

static int clientA_Hanndle(void *pObj, IPC_MSG_t *pMsg)
{
    int *pClient_Id = (int *)pObj;
    if(MSGTYPE_CLIENT_DATA == pMsg->msgType) {
        Data_t data = {0};
        memcpy(&data, pMsg->payload, sizeof(Data_t));
        printf("**********[A客户端(%d)]收到来自[B客户端]数据：a:%d , b:%d , c:%d***********\n", *pClient_Id, data.a, data.b , data.c);
    }else if(MSGTYPE_UPGRADE == pMsg->msgType){

    }
    return 0;
}

int main()
{
    /*新建A客户端，客户端ID为：A_CLI_ID*/
    IPC_client_create();
    int ret = IPC_client_init(A_CLI_ID);
    if(-1 == ret) {
        printf("IPCClient_A Create faild !!!\n");
        return -1;
    }
    int objA = A_CLI_ID;
    IPC_client_set_callback(&objA/*这个指针会传到 clientA_Hanndle 的pObj*/, clientA_Hanndle);

    /*等待B_CLI_ID客户端注册成功*/
    waittingTargetClientReady(B_CLI_ID);

    /*循环向B_CLI_ID客户端发送 MSGTYPE_UPGRADE 信息*/
    UPGRADE_t *pUpGrade = (UPGRADE_t *)malloc(sizeof(UPGRADE_t));
    memset(pUpGrade, 0, sizeof(UPGRADE_t));
    while(1)
    {
        sleep(2);   
        pUpGrade->a += 1;
        pUpGrade->b += 10;
        pUpGrade->c += 100;
        ret = IPC_client_sendData(B_CLI_ID, MSGTYPE_UPGRADE, pUpGrade, sizeof(UPGRADE_t));
        if(-1 == ret) {
            printf(" IPC_client_sendData faild !!!\n");    
            break;
        }   
    }
    
    return 0;
}

