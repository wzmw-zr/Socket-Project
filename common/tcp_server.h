/*************************************************************************
	> File Name: tcp_server.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 16时07分42秒
 ************************************************************************/

#ifndef _TCP_SERVER_H
#define _TCP_SERVER_H
void CheckArg(int argc, char **argv);
int GetSocket();
struct sockaddr_in GetSockAddrIN(char *port);
int CreateSocket(char *port);
pthread_attr_t GetDetachThreadAttr();
#endif
