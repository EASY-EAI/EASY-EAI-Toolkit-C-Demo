#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#include "ipc.h"

int main()
{
    /*新建服务端*/
    int ret = IPC_server_create(20);
    if(-1 == ret){
         printf("IPCServer Create faild !!!\n");
        return -1;
    }

    while(1) {
        sleep(2);
    }
    
    return 0;
}

