#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "ipcData.h"

#include "ipc.h"

static int clientB_Hanndle(void *pObj, IPC_MSG_t *pMsg)
{
    int *pClient_Id = (int *)pObj;
    if(MSGTYPE_CLIENT_DATA == pMsg->msgType) {
        
    }else if(MSGTYPE_UPGRADE == pMsg->msgType){
        UPGRADE_t upGrade = {0};
        memcpy(&upGrade, pMsg->payload, sizeof(UPGRADE_t));
        printf("**********[B客户端(%d)]收到来自[A客户端]数据：a:%d , b:%d , c:%d***********\n", *pClient_Id, upGrade.a, upGrade.b , upGrade.c);
    }
    return 0;
}

int main()
{
    /*新建B客户端，客户端ID为：B_CLI_ID*/
    IPC_client_create();
    int ret = IPC_client_init(B_CLI_ID);
    if(-1 == ret) {
        printf("IPCClient_B Create faild !!!\n");
        return -1;
    }
    int objB = B_CLI_ID;
    IPC_client_set_callback(&objB/*这个指针会传到 clientB_Hanndle 的pObj*/, clientB_Hanndle);
    
    /*循环向A客户端发送信息*/
    Data_t *pData = (Data_t *)malloc(sizeof(Data_t));
    memset(pData, 0, sizeof(Data_t));
    while (1)
    {
        sleep(2);
        pData->a += 1;
        pData->b += 10;
        pData->c += 100;
        ret = IPC_client_sendData(A_CLI_ID, MSGTYPE_CLIENT_DATA, pData, sizeof(Data_t));
        if(-1 == ret)
        {
            printf(" IPC_client_sendData faild !!!\n");    
            goto exit;
        }
    }
exit:
    return 0;
}

