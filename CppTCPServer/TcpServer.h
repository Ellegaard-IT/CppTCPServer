#include <WS2tcpip.h>

class TcpServer
{
public:
	void InitMethod();
	SOCKET BindIPandPort(SOCKET socket);
	SOCKET CreateSocket();
	SOCKET WaitConnection(SOCKET listeningSocket);
	void Closesocket(SOCKET socket);
	void WinSockShutDown();
};

