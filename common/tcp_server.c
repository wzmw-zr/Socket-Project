/*************************************************************************
	> File Name: tcp_server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 16时11分48秒
 ************************************************************************/

#include "head.h"
#include "tcp_server.h"

void CheckArg(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n");
        exit(1);
    }
}

int GetSocket() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    return sockfd;
}

struct sockaddr_in GetSockAddrIN(char *port) {
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port));
    server.sin_addr.s_addr = INADDR_ANY;
    return server;
}

int CreateSocket(char *port) {
    int sockfd = GetSocket();
    struct sockaddr_in address = GetSockAddrIN(port);
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(sockfd, 20) == -1) {
        perror("listen");
        exit(1);
    }
    return sockfd;
}

