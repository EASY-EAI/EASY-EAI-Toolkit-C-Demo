#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

/**
 * create a socket fd and connect to (host, service)
 */
static int tcp_client_create(const char *host, const char *service)
{    
    // 1.open tcp client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0){
        return -1;
    }

    // 2.clinet connect server
    struct sockaddr_in server_addr={0}; //server infomation
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(service));
    if(inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0){
        return -1;
    }
    if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        return -1;
    }

    return client_socket;
}

int main(void)
{
    char sendBuf[128] = "I am client";
    char recvBuf[128] = {0};

    int client_socket = tcp_client_create("127.0.0.1", "8080");

     read(client_socket, recvBuf, sizeof(recvBuf));
    write(client_socket, sendBuf, sizeof(sendBuf));
    close(client_socket);

    printf("recv from server: %s\n", recvBuf);

    return 0;
}
