#include "ServerListen.h"
#include <WS2tcpip.h>
#include <vector>
#include <iostream>

#pragma comment (lib, "ws2_32.lib")
using namespace std;

SOCKET ServerListen::ListenLoop(SOCKET clientSocket)
{
    char buf[4096];

    while (true)
    {
        ZeroMemory(buf, 4096);

        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == SOCKET_ERROR)
        {
            cerr << "error in recv message!" << endl;
            break;
        }
        else if (bytesReceived == 0)
        {
            cout << "client disconnected " << endl;
            break;
        }

        /* Interaction text goes here */

        send(clientSocket, buf, bytesReceived + 1, 0);
    }
    return clientSocket;
}