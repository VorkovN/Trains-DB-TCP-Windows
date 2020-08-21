#include "Server.h"

Server::Server() {
	DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}


	sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8127);
	addr.sin_family = AF_INET;

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
}

WSAData	Server::getWsaData() {
	return wsaData;
};

WORD Server::getDLLVersion() {
	return DLLVersion;
};

SOCKADDR_IN Server::getAddr() {
	return addr;
};

int* Server::getSizeofaddr() {
	return &sizeofaddr;
};

SOCKET Server::getSListen() {
	return sListen;
};
