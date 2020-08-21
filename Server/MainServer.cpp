#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <set>
#include "Server.h"
#include "Controller.h"
#pragma warning(disable: 4996)

Server server;
Controller controller;

void ClientHandler(SOCKET current_socket) {

	char from[64];
	char to[64];
	char freight_type[64];
	int cars_count;
	string msg;
	while (true) {
		try {

			if (recv(current_socket, from, sizeof(from), NULL) > 0
				&& recv(current_socket, to, sizeof(to), NULL) > 0
				&& recv(current_socket, freight_type, sizeof(freight_type), NULL) > 0
				&& recv(current_socket, (char*)&cars_count, sizeof(int), NULL) > 0)
					msg = controller.order(from, to, freight_type, cars_count - 48);
		}
		catch (exception ex) {
			msg = ex.what();
		}
		send(current_socket, msg.c_str(), msg.size(), NULL);
	}
}

int main(int argc, char* argv[]) {




	while (true) {
		SOCKET newConnection = accept(server.getSListen(), (SOCKADDR*)&server.getAddr(), server.getSizeofaddr());

		if (newConnection == 0) {
			cout << "Error #2\n";
		}
		else {
			cout << "\nClient Connected!\n";
			char msg_start[64] = "Hello. You can order transportation your freight\n";
			send(newConnection, msg_start, sizeof(msg_start), NULL);

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(newConnection), NULL, NULL);
		}
	}


	system("pause");
	return 0;
}