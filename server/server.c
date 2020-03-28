/*************************************************************************
	> File Name: server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 16时25分16秒
 ************************************************************************/

#include "head.h"
#include "tcp_server.h"

void chstr(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

void *work(void *arg) {
    int fd = *((int *) arg);
    if (send(fd, "You Are Here", sizeof("You Are Here"), 0) < 0) {
        perror("send");
        close(fd);
        return NULL;
    }
    while (1) {
        char msg[512] = {0};
        if (recv(fd, msg, sizeof(msg), 0) <= 0) {
            perror("error in recv!\n");
            break;
        }
        printf("recv： %s\n", msg);
        chstr(msg);
        if (send(fd, msg, strlen(msg), 0) < 0) {
            perror("error in send");
            break;
        }
        printf("Success in ECHO !\n");
    }
    close(fd);
    return NULL;
}

int main(int argc, char **argv) {
    CheckArg(argc, argv);
    int sockfd = CreateSocket(argv[1]);
    while (1) {
        int fd;
        pthread_t tid;
        if ((fd = accept(fd, NULL, NULL)) == -1) {
            perror("accept");
            continue;
        }
        int errno;
        if ((errno = pthread_create(&tid, NULL, work, (void *) &fd) == -1)) {
            fprintf(stderr, "%s\n", strerror(errno));
            continue;
        }
        if ((errno = pthread_detach(tid))) {
            fprintf(stderr, "%s\n", strerror(errno));
            continue;
        }
    }
    return 0;
}
