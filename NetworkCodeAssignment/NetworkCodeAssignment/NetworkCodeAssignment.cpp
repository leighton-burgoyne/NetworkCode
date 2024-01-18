// NetworkCodeAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <winsock2.h>
#include <ws2tcpip.h>
#include <tchar.h>
#include <stdio.h>
#include "iostream"
#include "Comms.h"
#include "Client.h"
#include "Server.h"

using namespace std;

int main()
{
    // Create instances for Server, Client and Comms Class
    Server server;
    Client client;
    Comms* comms = new Comms();
    SOCKADDR_STORAGE from;
    int fromlen;
    char hoststr[NI_MAXHOST], servstr[NI_MAXSERV];

    // Start server connection process with Winsock
    server.StartConnection(comms->wsaData);

    // Create a socket for the server
    comms->serverSocket = server.CreateSocket();

    // Start client connection process with Winsock
    client.StartConnection(comms->wsaData);

    // Create a socket for the client
    comms->clientSocket = client.CreateSocket();

    // Server Address and Port Info
    comms->srvService;
    comms->srvService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &comms->srvService.sin_addr.s_addr);
    comms->srvService.sin_port = htons(55555);

    // Connect Server to Client
    server.ConnectSocketToClient(comms->serverSocket, comms->srvService);

    // Test Server Connection
    server.TestSocket(comms->serverSocket);

    // Client Address and Port Info
    comms->clientService;
    comms->clientService.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &comms->clientService.sin_addr.s_addr);
    comms->clientService.sin_port = htons(55555);

    // Connect the Client to Server
    client.ConnectSocketToServer(comms->clientSocket, comms->clientService);

    // Accept Connection Request
    SOCKET acceptSocket = server.AcceptRequest(comms->serverSocket, from, fromlen);

    // Retrieve Connection Details
    server.GetConnectionDetails(from, fromlen, hoststr, servstr);

    while (comms->active) // Whilst Active
    {
        cout << "Enter Message: " << endl;
        cout << "(Type 'Quit' to exit the Application!)\n";
        cin.getline(comms->buffer, 200); // Handle the message input and store in buffer

        if (string(comms->buffer) == "Quit") { // If Quit Message detected
            cout << "Quitting Application" << endl;
            comms->active = false; // Stop the loop
        }

        client.SendMessages(comms->clientSocket, comms->buffer); // Handle sending the message to the server

        comms->byteCount = recv(acceptSocket, comms->buffer, 200, 0);

        if (comms->byteCount > 0)
        {
            cout << "Message received: " << comms->buffer << endl;
        }
        else
            WSACleanup();
    }
}

