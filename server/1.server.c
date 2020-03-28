/*************************************************************************
	> File Name: 1.server.thread.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月27日 星期五 07时35分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void CheckArg(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    } 
    return ;
}

int CreateSocket(char *port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(port));
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("bind");
        exit(1);
    }
    return sockfd;
}

int socket_create(int port) {
    int server_listen;
    if ((server_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_listen, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("bind");
        return -1;
    }
    return server_listen;
}

void chstr(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') str[i] -= 32;
    }
}

void *start(void *sockfd) {
    int commufd = *((int *) sockfd);
    char buffer[1024];
    int len;
    while ((len = recv(commufd, buffer, sizeof(buffer), 0)) > 0) {
        write(1, buffer, len);
    }
    close(commufd);
    return NULL;
}



int main(int argc, char **argv) {
    CheckArg(argc, argv);
    int listen_fd = CreateSocket(argv[1]);
    if (listen(listen_fd, 20) == -1) {
        perror("listen");
        exit(1);
    }
    while (1) {
        int sockfd;
        struct sockaddr_in address;
        socklen_t len = sizeof(address);
        if ((sockfd = accept(listen_fd, (struct sockaddr *) &address, &len)) == -1) {
            perror("accept");
            exit(1);
        } 
        pthread_t tid;
        int errno;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        if ((errno = pthread_create(&tid, &attr, start, (void *) &sockfd))) {
           fprintf(stderr, "%s\n", strerror(errno)); 
            exit(1);
        }
        pthread_attr_destroy(&attr);
    }
    return 0;
}
