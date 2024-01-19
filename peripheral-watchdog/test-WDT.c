#include <peripheral-watchdog.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler()
{
    int ret = wdt_close();
    if(ret < 0){
        printf("\n看门狗关闭失败！！！\n");
    }else if(ret == 0){
        printf("\n看门狗关闭成功！！！\n");
    }
    exit(0);
}

int main()
{
    int timeout = 60;
    int ret = wdt_open(timeout);
    if(ret < 0){
        printf("看门狗使能失败！！！\n");
    }else{
        printf("看门狗使能成功，溢出时间：%d（秒）\n", ret);
    }
    
    // 捕捉ctrl+c信号
    signal(SIGINT, handler);
    while (1)
    {
        sleep(3);
        ret = wdt_feeddog();
        if(ret < 0){
            printf("喂狗失败！！！\n");
        }else if(ret == 0){
            printf("喂狗成功！！！\n");
        }
    }
    return 0;
}
