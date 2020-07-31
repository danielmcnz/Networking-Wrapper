#include <stdio.h>

#include "../Wrapper/Sockets.h"

using namespace Networking;

using Networking::Socket;

void UDP();

int main()
{
	sockinfo sInfo;
	sInfo.port = "3591";
	sInfo.ip = 0;

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0);
	
	return 0;
}

void UDP()
{
	sockinfo sInfo;
	sInfo.port = "3591";
	sInfo.ip = 0;

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_DGRAM, IPPROTO_UDP, AI_PASSIVE);
	socket.Bind(sock);

	std::string sendmsg = "this is a test";

	while (true)
	{
		sockinfo sClientInfo;
		sClientInfo.port = "3591";

		std::string msg = socket.UDPRecv(sock, sClientInfo);

		printf("%s: %s", sClientInfo.ip, msg.c_str());

		// Send message
		Socket clientSocket(sClientInfo);
		SOCKET clientSock = clientSocket.Sock(AF_INET, SOCK_DGRAM,
			IPPROTO_UDP, 0);


		if (clientSocket.Bind(clientSock))
		{
			socket.UDPSend(sock, sendmsg);
		}
	}
}