#include "Client.h"

Client::Client() {
	DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		cout << "Error" << endl;
		exit(1);
	}

	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(8127);
	addr.sin_family = AF_INET;

	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		exit(1);
	}
	cout << "Connected!\n";
}

WSAData	Client::getWsaData() {
	return wsaData;
};

WORD Client::getDLLVersion() {
	return DLLVersion;
};

SOCKADDR_IN Client::getAddr() {
	return addr;
};

SOCKET Client::getConnection() {
	return Connection;
};