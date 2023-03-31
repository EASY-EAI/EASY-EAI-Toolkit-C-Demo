#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

/**
 * 1.create a AI_PASSIVE socket fd
 * 2.bind the socket
 */
static int udp_server_create(const char *service)
{
    uint16_t family = AF_INET; //地址族，AF_INET表示IPv4网际协议
    
    // 1.open udp server socket
    int server_socket = socket(family, SOCK_DGRAM, 0);
    if(server_socket < 0){
        return -1;
    }

    // 2.bind
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = family;
    server_addr.sin_port = htons(atoi(service));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //INADDR_ANY：表示无论是哪个IP地址，只要端口号是对的，都会去处理
    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        return -1;
    }

    return server_socket;
}

int main(void)
{
    char sendBuf[128] = "I am server";
    char recvBuf[128] = {0};
    
    int server_socket = udp_server_create("8080");

    struct sockaddr client_addr = {0};
    socklen_t len = sizeof(client_addr);
    //recvfrom是拥塞函数，没有数据就一直拥塞
    int count = recvfrom(server_socket, recvBuf, sizeof(recvBuf), 0, &client_addr, &len);
    if(count == -1){
        printf("recieve data fail!\n");
        return -1;
    }
    sendto(server_socket, sendBuf, strlen(sendBuf), 0, &client_addr, len);
    
    close(server_socket);
    
    printf("recv from client: %s\n", recvBuf);
    
    return 0;
}
