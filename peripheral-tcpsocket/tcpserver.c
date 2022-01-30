#include <stdio.h>
#include "tcpsocket.h"

int main(void)
{
    int listen_fd;
    int socket_fd;
    char ip[128];
    int port;
    char buf[128] = "I am server";

    listen_fd = tcp_server("127.0.0.1", "8080");
    socket_fd = tcp_server_accept(listen_fd, ip, &port);
    tcp_send(socket_fd, buf, sizeof(buf));
    tcp_recv(socket_fd, buf, sizeof(buf));
    tcp_close(socket_fd);
    printf("recv from client: %s\n", buf);
}
