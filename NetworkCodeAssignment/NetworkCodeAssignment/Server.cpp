// Server.cpp : This file contains the server connection functionality
//

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include "iostream"
#include "Server.h"
#include "Comms.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int Server::StartConnection(WSADATA& wsaData) {
	cout << "Configuring the Server...\n" << endl;
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		cout << "Error while locating Winsock dll on system" << endl;
		return 0;
	}
	else
	{
		cout << "Winsock dll found on system" << endl;
		cout << "Current status: " << wsaData.szSystemStatus << endl;
		return 1;
	}
}

SOCKET Server::CreateSocket() {
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Error whilst creating socket: " << WSAGetLastError() << endl;
		WSACleanup();
		return INVALID_SOCKET;
	}
	else
	{
		cout << "Socket created and OK" << endl;
		return serverSocket;
	}
}

int Server::ConnectSocketToClient(SOCKET serverSocket, sockaddr_in& srvService) {
	cout << "\nPlease wait, binding the Server to the Client...\n" << endl;
	if (bind(serverSocket, (SOCKADDR*)&srvService, sizeof(srvService)) == SOCKET_ERROR) {
		cout << "Binding Error: " << WSAGetLastError() << endl;
		closesocket(serverSocket);
		WSACleanup();
		return 0;
	}
	else
	{
		cout << "Binding Successful!" << endl;
		return 1;
	}
}

int Server::TestSocket(SOCKET serverSocket) {
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		cout << "Error while listening for connections: " << WSAGetLastError() << endl;
		return 0;
	}
	else
	{
		cout << "Listening for connections...\n" << endl;
		return 1;
	}
}

SOCKET Server::AcceptRequest(SOCKET ServerSocket, SOCKADDR_STORAGE& from, int& fromlen) {
	acceptSocket;
	fromlen = sizeof(from);
	acceptSocket = accept(serverSocket, (SOCKADDR*)&from, &fromlen);
	return acceptSocket;
}

int Server::GetConnectionDetails(SOCKADDR_STORAGE& from, int fromlen, char* hoststr, char* servstr) {
	// Get Client Details
	int retval;
	retval = getnameinfo((SOCKADDR*)&from,
		fromlen,
		hoststr,
		NI_MAXHOST,
		servstr,
		NI_MAXSERV,
		NI_NUMERICHOST | NI_NUMERICSERV);

	if (retval != 0) {
		cout << "Error while retrieving Connection Details: " << retval << endl;
		WSACleanup();
		return 0;
	}
	// Output Client Details
	cout << "Accepted connection from host " << hoststr << " and port " << servstr << endl;
}

int Server::StopConnection() {
	system("pause");
	WSACleanup();
	return 1;
}