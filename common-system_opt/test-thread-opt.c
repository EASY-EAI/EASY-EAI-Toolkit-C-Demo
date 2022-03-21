#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "system_opt.h"


void *testThreadBody(void *arg)
{
	int *share_para = (int *)arg;
	
	while(1)
	{
		printf("[testThread] --- share_para = %d\n", *share_para);
		if(*share_para > 5){
			printf("[testThread] --- exit\n");
			break;
		}
		sleep(1);
	}
	
	pthread_exit(NULL);
}

int main(void)
{	
	printf("\n======================== [thread_api_demo] =============================\n");
	pthread_t pId;
	int share_para = 0;
	if(0 == CreateNormalThread(testThreadBody, &share_para, &pId)){
		while(1){
			printf("[mainThread] --- share_para = %d\n", share_para);
			share_para++;
			
			if(share_para > 10)
				break;
			sleep(1);
		}
	}
	
	printf("[MainThread] --- exit\n");	
	
	return 0;
}
