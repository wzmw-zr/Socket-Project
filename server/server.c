/*************************************************************************
	> File Name: server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 22时30分30秒
 ************************************************************************/

#include "head.h"
#include "tcp_server.h"


int main(int argc, char ** argv) {
    CheckArg(argc, argv);    
    int server_listen = GetServerListen(argv[1]);
    if (server_listen == -1) {
        perror("listen");
        exit(1);
    }
    while (1) {
        int fd;
        pthread_t tid;
        if ((fd = accept(fd, NULL, NULL)) == -1) {
            perror("accept");
            continue;
        }
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&tid, &attr, work, (void *) &fd);
        pthread_attr_destroy(&attr);
    }
    return 0;
}
