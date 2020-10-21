// client.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

unsigned WINAPI recvFunc(void *arg)
{
	char buf[100];
	int len;
	SOCKET s = *((SOCKET*)arg);
	while(1)
	{
		len = recv(s, buf, 100, 0);
		buf[len] = 0;
		printf("%s", buf);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char buf[100];
	int len;
	WSADATA wsaData;
	SOCKET server_sock;
	sockaddr_in server;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(server_sock, (sockaddr*)&server, sizeof(server));
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)recvFunc, (LPVOID)&server_sock, 0, NULL);


	while(1)
	{
		fgets(buf, 100, stdin);
		len = strlen(buf);
		send(server_sock, buf, len, 0);
	}
	closesocket(server_sock);
	return 0;
}

