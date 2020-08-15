#include "TcpServer.h"
#include <iostream>
#include <WS2tcpip.h>
#include <vector>

#pragma comment (lib, "ws2_32.lib")
using namespace std;

int connectionID = 0;

void TcpServer::InitMethod()
{
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);
    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        std::cerr << "Can't init winsock!" << std::endl;
    }
}

SOCKET TcpServer::BindIPandPort(SOCKET socket)
{
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(11000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(socket, (sockaddr*)&hint, sizeof(hint));

    listen(socket, SOMAXCONN);
    return socket;
}

SOCKET TcpServer::CreateSocket()
{
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET)
    {
        cerr << "can't create a socket!";
        return NULL;
    }
    SOCKET socket = BindIPandPort(listening);
    return socket;
}

SOCKET TcpServer::WaitConnection(SOCKET listeningSocket)
{
    sockaddr_in client;
    int clientSize = sizeof(client);
    cout << "Listening for client!" << endl;
    SOCKET clientSocket = accept(listeningSocket, (sockaddr*)&client, &clientSize);

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];

    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port: " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port: " << ntohs(client.sin_port) << endl;
    }
    return clientSocket;
}

void TcpServer::Closesocket(SOCKET socket)
{
    closesocket(socket);
}

void TcpServer::WinSockShutDown()
{
    WSACleanup();
}