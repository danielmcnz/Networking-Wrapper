#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#include <stdio.h>
#include <iostream>
#include <sstream>

#define MAXBUFLEN 100

#pragma comment(lib, "Ws2_32.lib")

namespace Networking
{
	typedef struct
	{
		std::string port;
		char* ip;
	} sockinfo;

	class Socket
	{
	public:
		Socket(sockinfo sInfo);
		~Socket();

		SOCKET Sock(int family, int socktype, int protocol, int flags);
		void CloseSock(SOCKET s);
		int Connect(SOCKET s);
		int Bind(SOCKET s);
		int Listen(SOCKET s);

		std::string UDPRecv(SOCKET s, sockinfo& clientinfo);
		int UDPSend(SOCKET s, std::string sendmsg);

		std::string TCPRecv(SOCKET s);
		int TCPSend(SOCKET s, std::string sendmsg);
	private:
		void* get_in_addr(sockaddr* sa);
	private:
		sockinfo sInfo;
		addrinfo hints, * result;
		int iResult, numbytes;
	};
}