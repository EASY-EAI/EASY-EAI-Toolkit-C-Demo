/**
 *
 * Copyright 2022 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: ZJH <zhongjiehao@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef NETWORK_H
#define NETWORK_H

#include <stdbool.h>
#include <stdint.h>

#if defined(__cplusplus)
extern "C"{
#endif

// network resource view
extern int32_t get_dataflow_statistics(const char *device, int64_t *total_recv, int64_t *total_send);

// network parameter get or set
extern bool    get_ipv4_dhcp(const char *device);
extern int32_t set_ipv4_dhcp(const char *device);
extern int32_t set_ipv4_static(const char *device, const char *ip, const char *mask, const char *gateway);
extern int32_t add_second_ipv4(const char *device, const char *ip, const char *mask);
extern int32_t delete_second_ipv4(const char *device);
extern int32_t set_ipv4_dns_static(const char *device, const char *primary_dns,const char *alternative_dns);
extern int32_t set_wifi_WAP2(const char *device, const char *access, const char *password);
extern int32_t restart_network_device();

extern int32_t get_local_Mac(const char *device, char *mac, int mac_len);
extern int32_t get_local_Ip(const char *device, char *ip, int ip_len);
extern int32_t get_local_NetMask(const char *device, char *netMask, int netMask_len);
extern int32_t get_local_GateWay(const char *device, char *gateWay, int gateWay_len);

// network parameter format transform
extern bool ipv4_str_to_bin(const char *strIP, char *binIP);
extern bool mac_str_to_bin(const char *strMac, char *binMac);

extern bool address_invaild(const char *addr_IPv4);
extern bool compare_IpAddr(char *addr1, char *addr2);

extern char* netAddrToStr(uint64_t netAddr);
extern uint64_t strToNetAddr(const char *p_str);

#if defined(__cplusplus)
}
#endif

#endif
