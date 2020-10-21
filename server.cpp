// server.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

typedef struct _addr{
	SOCKET s;
	sockaddr_in client;
}ADDR;

__declspec(thread) SOCKET client_sock;
__declspec(thread) sockaddr_in client;

unsigned WINAPI SendFunc(void *arg)
{
	char buf[100];
	int len;
	SOCKET s = *((SOCKET*)arg);
	while(1)
	{
		fgets(buf, 100, stdin);
		len = strlen(buf);
		send(s, buf, len, 0);
	}
}

unsigned WINAPI Func(void * arg)
{
	char buf[100];
	int len;

	client_sock = ((ADDR*)arg)->s;
	memcpy(&client, &(((ADDR*)arg)->client), sizeof(client));
	printf("one client connected\n");
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendFunc, (LPVOID)&client_sock, 0, NULL);

	while(1){
		len = recv(client_sock, buf, 100, 0);
		buf[len] = 0;
		printf("%s", buf);
	}
	//closesocket(client_sock);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	SOCKET server_sock;
	int sock_len;
	sockaddr_in server;
	ADDR addr;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(9999);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(server_sock, (sockaddr*)&server, sizeof(server));

	listen(server_sock, 128);
	
	sock_len = sizeof(client);
	while(1)
	{
		client_sock = accept(server_sock, (sockaddr*)&client,&sock_len);
		addr.s = client_sock;
		memcpy(&addr.client, &client, sizeof(client));
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Func, (LPVOID)&addr, 0, NULL);
	}


	return 0;
}

