#pragma once
#include "Comms.h"

class Client : Comms {
public:
	int StartConnection(WSADATA& wsaData);
	SOCKET CreateSocket();
	int ConnectSocketToServer(SOCKET ClientSocket, sockaddr_in& clientService);
	int SendMessages(SOCKET clientSocket, char* buffer);
	int StopConnection();
};