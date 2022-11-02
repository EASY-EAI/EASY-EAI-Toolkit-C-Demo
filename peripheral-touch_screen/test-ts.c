#include <stdio.h>
#include <unistd.h>
#include "touchscreen.h"


int dataBase_opt_handle(uint32_t eType, int x , int y )
{
    uint32_t m_event = eType;
    if(0 != (m_event & TS_PRESS)){
        printf("****按下屏幕(x:%d, y:%d)****\n",x ,y);
    }else if (0 != (m_event & TS_RELEASE)) {
        printf("****松开屏幕(x:%d, y:%d)****\n",x ,y);
    }else if (0 != (m_event & TS_CLICK)) {
        printf("****单击屏幕(x:%d, y:%d)****\n",x ,y);   
    }else if (0 != (m_event & TS_DOUBLECLICK)) {
        printf("****双击屏幕(x:%d, y:%d)****\n",x ,y);   
    }else if (0 != (m_event & TS_LONGPRESS)) {
        printf("****长按屏幕(x:%d, y:%d)****\n",x ,y);   
    }else if (0 != (m_event & TS_DRAG)) {
        printf("****拖动屏幕(x:%d, y:%d)****\n",x ,y);   
    }
	return 0;
}



int main()
{
    Init_TsEven(NULL,0);//使用环境变量，非阻塞
    set_even_handle(dataBase_opt_handle);
    while (1)
    {
       sleep(1);
    }
    return 0;
}
