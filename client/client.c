/*************************************************************************
	> File Name: client.c
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 14时52分05秒
 ************************************************************************/

#include "head.h"
#include "tcp_client.h"

int main(int argc, char **argv) {
    int sockfd;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        return 1;
    }
    if ((sockfd = socket_connect(argv[1], atoi(argv[2]))) < 0) {
        perror("socket_connect");
        return 1;
    }
    return 0;
}
