/*************************************************************************
	> File Name: tcp_server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 22时32分08秒
 ************************************************************************/

#include "head.h"
#include "tcp_server.h"
int client_number;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void CheckArg(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }
}

int GetSocket() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) return -1;
    struct linger optval;
    optval.l_onoff = 1;
    optval.l_linger = 0;
    int errno;
    if ((errno = setsockopt(sockfd, SOL_SOCKET, SO_LINGER, &optval, sizeof(optval))) == -1) {
        perror("setsockopt");
        exit(1);
    }
    return sockfd;
}

struct sockaddr_in GetSockAddr(char *port) {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(port));
    address.sin_addr.s_addr = INADDR_ANY;
    return address;
}

int GetServerListen(char *port) {
    int sockfd;
    if ((sockfd = GetSocket()) == -1) {
        perror("socket");    
        exit(1);
    }
    struct sockaddr_in address = GetSockAddr(port);
    if (bind(sockfd, (struct sockaddr *)&address, (socklen_t) sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }
    if (listen(sockfd, 20) == -1) return -1;
    return sockfd;
}

void AddNumberHandler(int fd) {
    pthread_mutex_lock(&mutex);
    if (client_number == MAXCLIENT) {
        char buf[100] = "Sorry, the online devices is too much\n";
        send(fd, buf, strlen(buf), 0); 
        close(fd);
    } else client_number++;
    pthread_mutex_unlock(&mutex);
}

void DelNumberHandler(int fd) {
    pthread_mutex_lock(&mutex);
    client_number--;
    pthread_mutex_unlock(&mutex);
}

void *work(void *arg) {
    int fd = *((int *) arg);
    AddNumberHandler(fd);
    char buf[1024] = {0};
    int len;
    while ((len = recv(fd, buf, sizeof(buf), 0))) {
        write(1, buf, len);    
        send(fd, buf, len, 0);
    }
    DelNumberHandler(fd);
    close(fd);
}

