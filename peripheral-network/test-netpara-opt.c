#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include "network.h"


int main(int argc, char const *argv[])
{
    // set_ipv4_dhcp("eth0");
    // set_ipv4_dhcp("wifi");

    set_ipv4_static("eth0", "192.168.3.241", "255.255.255.0", "192.168.3.1");
    set_ipv4_static("wifi", "192.168.3.115", "255.255.255.0", "192.168.3.1");
    
    add_second_ipv4("eth0", "192.168.3.243", "255.255.255.0");
    add_second_ipv4("wifi", "192.168.3.111", "255.255.255.0");

    // delete_second_ipv4("eth0");
    // delete_second_ipv4("wifi");

    set_ipv4_dns_static("eth0", "8.8.8.8", "8.8.4.4");
    set_ipv4_dns_static("wifi", "8.8.8.8",NULL);

    //set_wifi_WAP2("123123-0H1YW8","123123");

    restart_network_device();
    return 0;
}
