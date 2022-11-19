#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

/**
 * create a socket fd and connect to (host, service)
 */
static struct sockaddr server_obj_create(const char *host, const char *service)
{
    struct sockaddr addr = {0};
    struct sockaddr_in server_addr = {0};
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(service));  //注意网络序转换
    server_addr.sin_addr.s_addr = inet_addr(host);
    //server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //INADDR_ANY：表示无论是哪个IP地址，只要端口号是对的，都会去处理

    memcpy(&addr, &server_addr, sizeof(server_addr));
    return addr;
}

int main(void)
{
    char sendBuf[128] = "I am client";
    char recvBuf[128] = {0};

    // 1.open udp socket
    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket < 0){
        return -1;
    }

    // 2.init dst server object
    struct sockaddr dstAddr = server_obj_create("127.0.0.1", "8080");
    
    sendto(client_socket, sendBuf, strlen(sendBuf), 0, &dstAddr, sizeof(dstAddr));
    struct sockaddr dataSrc = {0};
    socklen_t len = sizeof(dataSrc);
    recvfrom(client_socket, recvBuf, sizeof(recvBuf), 0, &dataSrc, &len);
    
    close(client_socket);

    printf("recv from server: %s\n", recvBuf);

    return 0;
}
