#include <stdio.h>

#include "../Wrapper/Sockets.h"

using namespace Networking;

using Networking::Socket;

void TCPServer();
void TCPClient();
void UDPServer();

int main()
{
	TCPClient();

	return 0;
}

void TCPClient()
{
	sockinfo sInfo("3591", "192.168.20.112");

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0);
	socket.Connect(sock);

	std::string msg = "dsfsddfs";
	socket.TCPSend(sock, msg);

	socket.CloseSock(sock);
}

/*
EXAMPLE TCP SERVER
	uses ipv4 to recieve messages from clients on port 3591
	prints out message received from client and ip i.e.

		192.168.20.112: hello world
*/

void TCPServer()
{
	sockinfo sInfo("3591", 0);

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_STREAM, IPPROTO_TCP, AI_PASSIVE);
	socket.Bind(sock);
	socket.Listen(sock);

	while (true)
	{
		socket.Accept(sock);

		sockinfo sClientInfo("3591", "192.168.20.112");
		std::string msg = socket.TCPRecv(sock, sClientInfo);

		printf("%s: %s", sClientInfo.ip, msg);
	}

	socket.CloseSock(sock);
}

/* 
EXAMPLE UDP SERVER 
	uses ipv4 to recieve messages from clients on port 3591
	prints out message received from client and ip i.e.

		192.168.20.112: hello world
*/

void UDPServer()
{
	sockinfo sInfo("3591", 0);

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