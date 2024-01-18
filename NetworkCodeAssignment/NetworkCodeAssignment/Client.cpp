// Client.cpp : This file contains the client connection functionality
//

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include "iostream"
#include "Client.h"
#include "Comms.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int Client::StartConnection(WSADATA& wsaData)
{
	cout << "\nConfiguring the Client...\n" << endl;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "Error while locating Winsock dll on system" << endl;
		return 0;
	}
	else
	{
		cout << "Winsock dll found on system" << endl;
		cout << "Current status: " << wsaData.szSystemStatus << endl;
	}
}

SOCKET Client::CreateSocket() {
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		cout << "Error whilst creating socket: " << WSAGetLastError() << endl;
		WSACleanup();
		return clientSocket;
	}
	else
	{
		cout << "Socket created and OK\n" << endl;
		return clientSocket;
	}
}

int Client::ConnectSocketToServer(SOCKET ClientSocket, sockaddr_in& clientService) {
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout << "Connection to Server successful!" << endl;
		cout << "Can start sending and receiving data..." << endl;
		return 1;
	}
}

int Client::SendMessages(SOCKET clientSocket, char* buffer) {
	byteCount = send(clientSocket, buffer, 200, 0);

	if (byteCount > 0)
	{
		cout << "Message sent: " << buffer << endl;
		return 1;
	}
	else
		WSACleanup();
		return 0;
}

int Client::StopConnection() {
	system("pause");
	WSACleanup();
	return 1;
}