/*************************************************************************
	> File Name: server.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 14时41分26秒
 ************************************************************************/
#include "head.h"
#include "tcp_server.h"

int main(int argc, char **argv) {
    int port,server_listen;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        return 1;
    }
    return 0;
}
