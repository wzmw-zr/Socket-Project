/*************************************************************************
	> File Name: 5.client.transfer.file.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月23日 星期一 20时36分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define CONTENTSIZE 256

int GetFile(char *filepath) {
    int fd;
    if ((fd = open(filepath, O_RDWR)) <= 0) {
        perror(filepath);
        exit(1);
    }
    return fd;
}

int GetSocket() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    return sockfd;
}

struct sockaddr_in GetSockAddrIN(char *IP, char *port) {
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(port));
    if (inet_aton(IP, &(server.sin_addr)) == 0) {
        perror("inet_aton");
        exit(1);
    }
    return server;
}

void ReadAndSend(int fd, int sockfd) {
    char content[CONTENTSIZE + 5] = {0};
    int readsize;
    while ((readsize = read(fd, content, CONTENTSIZE)) > 0) {
        if (send(sockfd, content, readsize, 0) == -1) {
            perror("send");
            exit(1);
        } 
    }
    if (readsize == -1) {
        perror("readsize");
        exit(1);
    }
}

int socket_connect(char *host, char *port) {
    int sockfd = GetSocket();
    struct sockaddr_in server = GetSockAddrIN(host, port);
    if (connect(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        perror("connect");
        return -1;
    }
    return sockfd;
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s IP Port Filepath\n", argv[0]);
        exit(1);
    }
    int fd = GetFile(argv[3]);
    int sockfd = GetSocket();
    struct sockaddr_in server = GetSockAddrIN(argv[1], argv[2]);
    if (connect(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        perror("connect");
        exit(1);
    }
    ReadAndSend(fd, sockfd);
    close(fd);
    close(sockfd);
    return 0;
}
