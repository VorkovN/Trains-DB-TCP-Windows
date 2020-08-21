#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <vector>
#include "Client.h"
#pragma warning(disable: 4996)

using namespace std;


Client client;


void ClientHandler() {
	char msg[64];
	while (true) {
		if (recv(client.getConnection(), msg, sizeof(msg), NULL) > 0) {
			cout << msg << endl;
			memset(msg, 0, 64);
			Sleep(50);
		}
	}
}


int main(int argc, char* argv[]) {

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);

	char from[64];
	char to[64];
	char freight_type[64];
	char cars_count[64];
	while (true) {
		Sleep(100);
		cout << "Input city1" << endl;
		cin.getline(from, sizeof(from));
		cout << "Input city2" << endl;;
		cin.getline(to, sizeof(to));
		cout << "Input type of freight (liquid, wood or ore)" << endl;;
		cin.getline(freight_type, sizeof(freight_type));
		cout << "Input count of cars" << endl;
		cin.getline(cars_count, sizeof(cars_count));
		send(client.getConnection(), from, sizeof(from), NULL);
		send(client.getConnection(), to, sizeof(to), NULL);
		send(client.getConnection(), freight_type, sizeof(freight_type), NULL);
		send(client.getConnection(), cars_count, sizeof(int), NULL);
		cin.clear();
		cout << endl;
	}

	system("pause");
	return 0;
}
