// Comms.h : This header file contains any functionality that is common across the Server and Client classes
//

#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include "iostream"

#pragma comment(lib, "Ws2_32.lib")

class Comms
{
public:
	SOCKET clientSocket;
	SOCKET serverSocket, acceptSocket; // Socket Types
	int port = 55555; // Socket Port
	WSADATA wsaData; // WSADATA
	int wsaerr; // wsaerr int for errors
	WORD wVersionRequested = MAKEWORD(2, 2);
	sockaddr_in clientService; // Socket Address for Client
	sockaddr_in srvService; // Socket Address for Server
	char buffer[200]; // Buffer for Sending and Receiving Messages
	int byteCount; // Byte Count for determining whether message is valid
	bool active = true; // Is Message Loop Active?
};