#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>

/**
 * convert numberic ip in struct src to char *
 */
static int inet_generic_ntop(struct sockaddr *src, char *ip, int size)
{
    struct sockaddr_in *inet4;
    struct sockaddr_in6 *inet6;
    
    switch(src->sa_family)
    {
        case AF_INET:
            inet4 = (struct sockaddr_in *)src;
            if(inet_ntop(AF_INET, (void *)&inet4->sin_addr, ip, size) == NULL) {
                return -1;
            }
            return 0;
        case AF_INET6:
            inet6 = (struct sockaddr_in6 *)src;
            if(inet_ntop(AF_INET6, (void *)&inet6->sin6_addr, ip, size) == NULL) {
                return -1;
            }
            return 0;
        default:
            return -1;
    }
}

/**
 * convert port in struct src to local machine byte order (little-endian or big-endian)
 */
static int inet_generic_port(struct sockaddr *src, int *port)
{
    struct sockaddr_in *inet4;
    struct sockaddr_in6 *inet6;
    
    switch(src->sa_family)
    {
        case AF_INET:
            inet4 = (struct sockaddr_in *)src;
            if(port) {
                *port = ntohs(inet4->sin_port);
            }else{
                return -1;
            }
            return 0;
        case AF_INET6:
            inet6 = (struct sockaddr_in6 *)src;
            if(port) {
                *port = ntohs(inet6->sin6_port);
            }else{
                return -1;
            }
            return 0;
        default:
            return -1;
    }
}

/**
 * public interface for accept
 */
int tcp_server_accept(int server_socket, char *cliIp, int *pCliPort)
{
    struct sockaddr addr;
    uint32_t addr_len = sizeof(struct sockaddr);

    int client_socket = accept(server_socket, &addr, &addr_len);
    if(client_socket == -1){
        return -1;
    }

    if(cliIp) {
        if(-1 == inet_generic_ntop(&addr, cliIp, 128)){
            return -1;
        }
    }
    if(pCliPort) {
        if(-1 == inet_generic_port(&addr, pCliPort)){
            return -1;
        }
    }

    return client_socket;
}

/**
 * 1.create a socket fd
 * 2.bind the socket
 * 3.listen the socket
 */
static int tcp_server_create(/*const char *host, */const char *service)
{
    uint16_t family = AF_INET; //地址族，AF_INET表示IPv4网际协议
    
    // 1.open tcp server socket
    int listen_fd = socket(family, SOCK_STREAM, 0);
    if(listen_fd < 0){
        return -1;
    }

    // 1.1.set socket reuse
    // (使处于TIME_WAIT状态下的socket可以重复绑定使用)
    int on = 1;
    if(setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1){
        return -1;
    }

    // 2.bind
	struct sockaddr_in srvaddr = {0};
	srvaddr.sin_family = family;
	srvaddr.sin_port = htons(atoi(service));
	//srvaddr.sin_addr.s_addr = inet_addr(host); // IP地址
	srvaddr.sin_addr.s_addr = htonl(INADDR_ANY);  //INADDR_ANY：表示无论是哪个IP地址，只要端口号是对的，都会去处理
    if(bind(listen_fd, (struct sockaddr*)&srvaddr, sizeof(srvaddr)) == -1){
        return -1;
    }

    // 3.listen
    if(listen(listen_fd, 1024) == -1){
        return -1;
    }

    return listen_fd;
}

int main(void)
{
    char sendBuf[128] = "I am server";
    char recvBuf[128] = {0};
    
    int server_socket = tcp_server_create("8080");
    
    char client_ip[128];
    int  client_port;
    int  client_socket = tcp_server_accept(server_socket, client_ip, &client_port);
    
    write(client_socket, sendBuf, strlen(sendBuf));
     read(client_socket, recvBuf, sizeof(recvBuf));
    
    close(client_socket);
    close(server_socket);
    
    printf("client info[ip:(%s) -- port:(%d)]\n", client_ip, client_port);
    printf("recv from client: %s\n", recvBuf);
    
    return 0;
}
