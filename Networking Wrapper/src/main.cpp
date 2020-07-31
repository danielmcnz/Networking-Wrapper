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

/* 
EXAMPLE UDP SERVER 
	uses ipv4 to recieve messages from clients on port 3591
	prints out message received from client and ip i.e.

		192.168.20.112: hello world
*/

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
	}
}