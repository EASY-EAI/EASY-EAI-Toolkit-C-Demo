#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "system_opt.h"


void *testThreadBody(void *arg)
{
	int *share_para = (int *)arg;
	
	while(1)
	{
		printf("[tesThread] --- share_para = %d\n", *share_para);
		if(*share_para > 10){
			printf("[tesThread] --- exit\n");
			break;
		}
		sleep(1);
	}
	
	pthread_exit(NULL);
}

void network_parameter_get_set_api_demo()
{
#define MAX_MAC_LEN 6
#define MAX_IP_LEN 20

    char hexMac[MAX_MAC_LEN];
    char strMac[3*MAX_MAC_LEN+1] = {0};
    if(0 == get_local_Mac("eth0", hexMac, MAX_MAC_LEN)) {
		sprintf(strMac, "%02x:%02x:%02x:%02x:%02x:%02x", hexMac[0], hexMac[1], hexMac[2], hexMac[3], hexMac[4], hexMac[5]);
		printf("get mac succ: %s\n", strMac);
	}
	
    char ip[MAX_IP_LEN];
    if(0 == get_local_Ip("eth0", ip, MAX_IP_LEN)) {
		printf("get ip  succ: %s\n", ip);
	}
	
	set_net_ipv4("192.168.1.151", "255.255.255.0", "192.168.1.1");
    if(0 == get_local_Ip("eth0", ip, MAX_IP_LEN)) {
		printf("set ip  succ: %s\n", ip);
	}
	
	return ;
}

void network_parameter_convert_api_demo()
{
	char *strMac = "BC:8D:0A:7F:85:5E";
	char mac[6] = {0};
	if(mac_str_to_bin(strMac, mac)){
		printf("[mac  convert] = %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	}
	
	char *strIP = "192.168.1.233";
	char ipAddr[4] = {0};
	if(ipv4_str_to_bin(strIP, ipAddr)){
		printf("[ipv4 convert] = %d.%d.%d.%d\n", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
	}
	
	
	uint64_t netAddr = strToNetAddr("192.168.1.233");
	printf("[netAddr] = %llu \n", netAddr);
	printf("[strAddr] = %s \n", netAddrToStr(netAddr));
	
	return ;
}


int main(void)
{
	printf("\n=================== [network_parameter_api_demo] =======================\n");
	network_parameter_get_set_api_demo();
	network_parameter_convert_api_demo();
	
	char *ipAddr1 = "192.168.001.110";
	char *ipAddr2 = "192.168.01.110";
	bool bIsSam = compare_IpAddr(ipAddr1, ipAddr2);
	if(bIsSam){
		printf("ip [%s] & [%s] is sam\n", ipAddr1, ipAddr2);
	}else{
		printf("ip [%s] & [%s] isn't sam\n", ipAddr1, ipAddr2);
	}
	
	printf("\n================= [system_time_parameter_api_demo] =====================\n");
	printf("current timeval  = %llu us\n", get_timeval_us());
	printf("current timeval  = %llu ms\n", get_timeval_ms());
	printf("current timeval  = %llu s\n", get_timeval_s());
	printf("current timeStamp = %d\n", get_time_stamp());
	uint32_t curDate = 0, curTime = 0;
	set_system_date_time(2021, 12, 22, 11, 14, 59);
	get_system_date_time(&curDate, &curTime);
	printf("current date = %u, time = %u\n", curDate, curTime);
	
	
	printf("\n======================== [thread_api_demo] =============================\n");
	pthread_t pId;
	int share_para = 0;
	if(0 == CreateNormalThread(testThreadBody, &share_para, &pId)){
		while(1){
			printf("[mainThread] --- \n");
			share_para++;
			sleep(1);
		}
	}
	
	return 0;
}
