#include <stdio.h>
#include "tcpsocket.h"

int main(void)
{
    int socket_fd;
    char buf[128];

    socket_fd = tcp_client("127.0.0.1", "8080");
    tcp_recv(socket_fd, buf, sizeof(buf));
    printf("recv from server: %s\n", buf);
    strcpy(buf, "I am client");
    tcp_send(socket_fd, buf, sizeof(buf));
    tcp_close(socket_fd);
}
