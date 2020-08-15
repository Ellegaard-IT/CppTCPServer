#include <iostream>
#include <WS2tcpip.h>
#include "TcpServer.h"
#include "ServerListen.h"
#include <vector>
#include <thread>

using namespace std;

int clientsCounter;
vector<thread> connectionsList;

struct ConnectionGenerator
{
    int id;
    SOCKET clientSocket;
    SOCKET serverSocket;
    thread runningThreadID;
};

int main()
{
    TcpServer serverStarter;
    ServerListen *clientListener;
    serverStarter.InitMethod();
    SOCKET serverSocket = serverStarter.CreateSocket();
    SOCKET clientSocket;
    while (true)
    {
        try
        {
            clientSocket = serverStarter.WaitConnection(serverSocket);
            clientListener = new ServerListen();
            thread threadStarter(&ServerListen::ListenLoop, clientListener, clientSocket);
            /*auto connection = [id = clientsCounter, client = clientSocket, server = serverSocket](ConnectionGenerator a) {
                                                                                a.id = id;
                                                                                a.clientSocket = client;
                                                                                return a; 
                                                                                };*/
            //connectionsList.push_back(threadStarter);
            threadStarter.detach();
        }
        catch (const std::exception& e)
        {
            cout << "" << e.what() << endl;
        }
    }
    serverStarter.Closesocket(clientSocket);
    serverStarter.Closesocket(serverSocket);
    serverStarter.WinSockShutDown();

    delete clientListener;
}

