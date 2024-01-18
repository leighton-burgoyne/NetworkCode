#pragma once
#include "Comms.h"

class Server : Comms {
public:
	int StartConnection(WSADATA& wsaData);
	SOCKET CreateSocket();
	int ConnectSocketToClient(SOCKET ServerSocket, sockaddr_in& srvService);
	int TestSocket(SOCKET ServerSocket);
	SOCKET AcceptRequest(SOCKET ServerSocket, SOCKADDR_STORAGE& from, int& fromlen);
	int GetConnectionDetails(SOCKADDR_STORAGE& from, int fromlen, char* hoststr, char* servstr);
	int StopConnection();
};