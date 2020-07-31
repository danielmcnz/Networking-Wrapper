#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <stdio.h>
#include <iostream>
#include <sstream>

#define MAXBUFLEN 100
#define BACKLOG 5

#pragma comment(lib, "Ws2_32.lib")

namespace Networking
{
	typedef struct sockinfo
	{
		sockinfo() = default;
		sockinfo(std::string port, std::string ip)
			:
			port(port),
			ip(ip)
		{}
		std::string port;
		std::string ip;
	};

	class Socket
	{
	public:
		Socket(sockinfo sInfo);
		~Socket();

		SOCKET Sock(int family, int socktype, int protocol, int flags);
		void CloseSock(SOCKET s);
		int Connect(SOCKET s);
		int Bind(SOCKET s);
		int Listen(SOCKET s, int backlog = 5);
		int Accept(SOCKET s);

		std::string UDPRecv(SOCKET s, sockinfo& clientinfo);
		int UDPSend(SOCKET s, std::string sendmsg);

		std::string TCPRecv(SOCKET s, sockinfo& clientinfo);
		int TCPSend(SOCKET s, std::string sendmsg);
	private:
		void* get_in_addr(sockaddr* sa);
	private:
		sockinfo sInfo;
		addrinfo hints, * result;
		int iResult, numbytes;
	};
}