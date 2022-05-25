/**
 *
 * Copyright 2021 by Guangzhou Easy EAI Technologny Co.,Ltd.
 * website: www.easy-eai.com
 *
 * Author: CHM <chenhaiman@easy-eai.com>
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * License file for more details.
 * 
 */

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

int inet_generic_ntop(struct sockaddr *src, char *ip, int size);
int inet_generic_port(struct sockaddr *src, int *port);
int inet_resolve(const char *host, const char *service, 
                 struct addrinfo **res, int ai_passive);
int tcp_server_socket(const char *host, const char *service, 
                      struct sockaddr *addr, int *addr_len);
int tcp_client_socket(const char *host, const char *service,
                      struct sockaddr *server_addr, int *addr_len);
int set_socket_reuseaddr(int socket_fd);
int set_socket_nonblocking(int socket_fd);
int tcp_server_bind(int socket_fd, const struct sockaddr *addr,
                    int addr_len);
int tcp_server_listen(int socket_fd, int backlog);
int tcp_server_accept(int socket_fd, char *ip, int *port);
int tcp_client_connect(int socket_fd, const struct sockaddr *server_addr,
                       int addr_len);
int tcp_client(const char *host, const char *service);
int tcp_server(const char *host, const char *service);
void tcp_close(int socket_fd);
int tcp_recv(int socket_fd, void *buf, int size);
int tcp_send(int socket_fd, const void *buf, int size);

#ifdef __cplusplus
}
#endif
#endif
