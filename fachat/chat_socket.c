#include "chat_socket.h"

int socket_bind(int sockfd, const char *bind_ipaddr, const int port)
{
    struct sockaddr_in bindaddr;

    bindaddr.sin_family = AF_INET;
    bindaddr.sin_port = htons(port);
    if (bind_ipaddr == NULL || *bind_ipaddr == '\0') {
        bindaddr.sin_addr.s_addr = INADDR_ANY;
    } else {
        if (inet_aton(bind_ipaddr, &bindaddr.sin_addr) == 0) {
            return -1;
        }
    }

    if (bind(sockfd, (struct sockaddr*)&bindaddr, sizeof(bindaddr)) < 0)
        return -2;

    return 0;
}

int set_socket_server(const char *bind_ipaddr, const int port)
{
    int sockfd;
    int result;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        return -1;

    result = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &result, sizeof(int))<0) {
        close(sockfd);
        return -2;
    }

    if (socket_bind(sockfd, bind_ipaddr, port) != 0) {
        close(sockfd);
        return -3;
    }
    
    if (listen(sockfd, 1024) < 0) {
        close(sockfd);
        return -4;
    }

    return sockfd;
}
