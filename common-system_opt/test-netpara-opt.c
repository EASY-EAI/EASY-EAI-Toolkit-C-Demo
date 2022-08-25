#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "system_opt.h"

int main(void)
{
#define MAX_MAC_LEN 6
#define MAX_IP_LEN 20
	printf("\n=================== [network parameter get and set api demo] =======================\n");
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
	
	set_net_ipv4("eth0","192.168.1.151", "255.255.255.0", "192.168.1.1");
    if(0 == get_local_Ip("eth0", ip, MAX_IP_LEN)) {
		printf("set ip  succ: %s\n", ip);
	}
	
	printf("\n=========== [network srting format convert to array format api demo] ===============\n");
	char *strMac2 = "BC:8D:0A:7F:85:5E";
	char mac[6] = {0};
	if(mac_str_to_bin(strMac2, mac)){
		printf("[mac  convert] = %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	}
	
	char *strIP = "192.168.1.233";
	char ipAddr[4] = {0};
	if(ipv4_str_to_bin(strIP, ipAddr)){
		printf("[ipv4 convert] = %d.%d.%d.%d\n", ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
	}
	
	printf("\n========== [network srting format convert to netAddr format api demo] ==============\n");
	uint64_t netAddr = strToNetAddr("192.168.1.233");
	printf("[netAddr] = %llu \n", netAddr);
	printf("[strAddr] = %s \n", netAddrToStr(netAddr));
	
	printf("\n=================== [network srting format compare api demo] =======================\n");
	char *ipAddr1 = "192.168.001.110";
	char *ipAddr2 = "192.168.01.110";
	bool bIsSam = compare_IpAddr(ipAddr1, ipAddr2);
	if(bIsSam){
		printf("ip [%s] & [%s] is sam\n", ipAddr1, ipAddr2);
	}else{
		printf("ip [%s] & [%s] isn't sam\n", ipAddr1, ipAddr2);
	}
	
	return 0;
}
