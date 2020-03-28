/*************************************************************************
	> File Name: tcp_server.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 22时31分20秒
 ************************************************************************/

#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H
void CheckArg(int argc, char **argv);
int GetServerListen(char *port);
int GetSocket();
struct sockaddr_in GetSockAddr(char *port);
void AddNumberHandler(int fd);
void DelNumberHandler(int fd);
void *work(void *arg);

#define MAXCLINET 1024
//int client_number;
//pthread_mutex_t mutex;
#endif
