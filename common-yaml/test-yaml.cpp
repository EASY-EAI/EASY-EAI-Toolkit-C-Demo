#include <iostream>
#include <fstream> 
#include "yaml-cpp/yaml.h"
#include <arpa/inet.h>

std::string mask_transition_cidr(std::string ip_str , std::string mask_str )
{
    struct in_addr mask_addr;
    inet_pton(AF_INET, mask_str.c_str(), &mask_addr);
    int mask = 0;
    for (int i = 0; i < 32; i++) {
        if ((mask_addr.s_addr >> i) & 1) {
        mask++;
        }
    }
    std::string cidr = ip_str + "/" + std::to_string(mask);
    printf("ip_str:%s , mask_str:%s , cidr:%s , mask:%d\n",ip_str.c_str(),mask_str.c_str(),cidr.c_str(),mask);
    return cidr;
}



int main() {
    // 加载YAML文件
    YAML::Node config = YAML::LoadFile("/etc/netplan/99_config.yaml");
    // =====================修改eth0的参数============================
    //把DHCP禁用
    config["network"]["ethernets"]["eth0"]["dhcp4"] = "false";
    // 修改eth0的IP地址
        // 输入 IP 地址和子网掩码
    std::string eth0_ip_str = "192.168.3.240";
    std::string eth0_mask_str = "255.255.255.0";
    std::string eth0_cidr = mask_transition_cidr(eth0_ip_str,eth0_mask_str);
    config["network"]["ethernets"]["eth0"]["addresses"].push_back(eth0_cidr);
    // 修改eth0的DNS地址
    YAML::Node addresses_eht0_dns = YAML::Load("[8.8.8.8,8.8.4.4]");//[8.8.8.8, 8.8.4.4]这是一个序列，需要转换
    config["network"]["ethernets"]["eth0"]["nameservers"]["addresses"] = addresses_eht0_dns;
    // 修改eth0的routes地址
    config["network"]["ethernets"]["eth0"]["routes"][0]["to"] = "0.0.0.0/0";
    config["network"]["ethernets"]["eth0"]["routes"][0]["via"] = "192.168.3.1";
    config["network"]["ethernets"]["eth0"]["routes"][0]["metric"] = "100";
    // =====================修改wifis的参数============================
    //把DHCP禁用
    config["network"]["wifis"]["wlan0"]["dhcp4"] = "false";
    // 修改eth0的IP地址
    // 输入 IP 地址和子网掩码
    std::string wifi_ip_str = "192.168.3.114";
    std::string wifi_mask_str = "255.255.255.0";
    std::string wifi_cidr = mask_transition_cidr(wifi_ip_str,wifi_mask_str);
    config["network"]["wifis"]["wlan0"]["addresses"].push_back(wifi_cidr);
    // 修改eth0的DNS地址
    YAML::Node addresses_wifi_dns = YAML::Load("[8.8.8.8,8.8.4.4]");//[8.8.8.8, 8.8.4.4]这是一个序列，需要转换
    config["network"]["wifis"]["wlan0"]["nameservers"]["addresses"] = addresses_wifi_dns;
    // 修改eth0的routes地址
    config["network"]["wifis"]["wlan0"]["routes"][0]["to"] = "0.0.0.0/0";
    config["network"]["wifis"]["wlan0"]["routes"][0]["via"] = "192.168.3.1";
    config["network"]["wifis"]["wlan0"]["routes"][0]["metric"] = "100";
    config["network"]["wifis"]["wlan0"]["access-points"]["HUAWEI-0H1YW8"]["password"] = "lmo12345678";
    // =============================================================
    // 将修改后的YAML文档写回到文件中
    std::ofstream fout("/etc/netplan/99_config.yaml");
    fout << config;
    fout.close();

    return 0;
}