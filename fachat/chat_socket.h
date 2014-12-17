#ifndef _CHAT_SOCKET_H
#define _CHAT_SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int socket_bind(int sockfd, const char *bind_ipaddr, const int port);

int set_socket_server(const char *bind_ipaddr, const int port);

#endif /* _CHAT_SOCKET_H */
