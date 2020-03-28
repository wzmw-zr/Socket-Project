/*************************************************************************
	> File Name: tcp_client.h
	> Author:赵睿 
	> Mail: 1767153298@qq.com
	> Created Time: 2020年03月28日 星期六 16时10分26秒
 ************************************************************************/

#ifndef _TCP_CLIENT_H
#define _TCP_CLIENT_H
int GetSocket();
struct sockaddr_in GetSockAddrIN(char *IP, char *port);
#endif
