#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <set>
#pragma warning(disable: 4996)

using namespace std;

class Server{
public:
	Server();

	WSAData getWsaData();
	WORD getDLLVersion();
	SOCKADDR_IN getAddr();
	int* getSizeofaddr();
	SOCKET getSListen();

private:
	WSAData wsaData;
	WORD DLLVersion;
	SOCKADDR_IN addr;
	int sizeofaddr;
	SOCKET sListen;
};

