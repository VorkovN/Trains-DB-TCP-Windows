#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#pragma warning(disable: 4996)

using namespace std;

class Client {
public:
	Client();

	WSAData getWsaData();
	WORD getDLLVersion();
	SOCKADDR_IN getAddr();
	SOCKET getConnection();

private:
	SOCKET Connection;
	WSAData wsaData;
	WORD DLLVersion;
	SOCKADDR_IN addr;
};

