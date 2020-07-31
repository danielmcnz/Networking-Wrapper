#include "Sockets.h"

Networking::Socket::Socket(sockinfo sInfo)
	:
	sInfo(sInfo)
{
	WSAData wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("wsastartip falied\n");
	}
}

Networking::Socket::~Socket()
{
	WSACleanup();
}

SOCKET Networking::Socket::Sock(int family, int socktype, int protocol, int flags)
{
	SOCKET s;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = family;
	hints.ai_socktype = socktype;
	hints.ai_protocol = protocol;
	hints.ai_flags = flags;

	iResult = getaddrinfo(sInfo.ip.c_str(), sInfo.port.c_str(), &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed\n");
		return 1;
	}

	s = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (s == SOCKET_ERROR)
	{
		printf("socket failed\n");
		return 1;
	}

	return s;
}

void Networking::Socket::CloseSock(SOCKET s)
{
	closesocket(s);
}

int Networking::Socket::Connect(SOCKET s)
{
	iResult = connect(s, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("connect failed");
		return 1;
	}

	return 0;
}

int Networking::Socket::Bind(SOCKET s)
{
	iResult = bind(s, result->ai_addr, result->ai_addrlen);
	if (iResult == SOCKET_ERROR)
	{
		printf("\nbind failed\n");
		return 1;
	}

	return 0;
}

int Networking::Socket::Listen(SOCKET s, int backlog)
{
	iResult = listen(s, backlog);
	if (iResult != 0)
	{
		printf("listen failed");
		return 1;
	}

	return 0;
}

int Networking::Socket::Accept(SOCKET s)
{
	sockaddr_storage client;
	socklen_t size;

	size = sizeof(client);

	iResult = accept(s, (sockaddr*)&client, &size);
	if (iResult != 0)
	{
		printf("accept failed");
		return 1;
	}

	return 0;
}

std::string Networking::Socket::UDPRecv(SOCKET s, sockinfo& clientinfo)
{
	sockaddr client;
	socklen_t clientlen = sizeof(client);
	char msgbuffer[MAXBUFLEN];
	char clientaddr[INET6_ADDRSTRLEN];

	numbytes = recvfrom(s, msgbuffer, MAXBUFLEN - 1, 0,
		(sockaddr*)&client, &clientlen);
	if (numbytes == SOCKET_ERROR)
	{
		printf("recvfrom failed\n");
	}

	if (numbytes == 0)
	{
		printf("zero bytes");
	}

	inet_ntop(client.sa_family, get_in_addr((sockaddr*)&client),
		clientaddr, sizeof(clientaddr));

	clientinfo.ip = new char[INET6_ADDRSTRLEN];

	for (int i = 0; i < INET6_ADDRSTRLEN; ++i)
	{
		clientinfo.ip[i] = clientaddr[i];
	}

	msgbuffer[numbytes] = '\0';

	return msgbuffer;
}

int Networking::Socket::UDPSend(SOCKET s, std::string sendmsg)
{
	numbytes = sendto(s, sendmsg.c_str(), sendmsg.length(), 0,
		result->ai_addr, result->ai_addrlen);
	if (numbytes == SOCKET_ERROR)
	{
		printf("sendto failed\n");
		return 1;
	}

	printf("Send %s byte packet to %s\n", numbytes, sInfo.ip);

	return 0;
}

std::string Networking::Socket::TCPRecv(SOCKET s, sockinfo& clientinfo)
{
	sockaddr client;
	socklen_t clientlen = sizeof(client);
	char msgbuffer[MAXBUFLEN];
	char clientaddr[INET6_ADDRSTRLEN];
	numbytes = recv(s, msgbuffer, sizeof(msgbuffer), 0);
	if(numbytes == SOCKET_ERROR)
	{
		printf("recv failed\n");
	}

	inet_ntop(client.sa_family, get_in_addr((sockaddr*)&client), clientaddr,
		sizeof(clientaddr));

	clientinfo.ip = new char[INET6_ADDRSTRLEN];

	for (int i = 0; i < INET6_ADDRSTRLEN; ++i)
	{
		clientinfo.ip[i] = clientaddr[i];
	}

	msgbuffer[numbytes] = '\0';

	return msgbuffer;
}

int Networking::Socket::TCPSend(SOCKET s, std::string sendmsg)
{
	numbytes = send(s, (char*)sendmsg.c_str(), sizeof(sendmsg), 0);
	if (numbytes == SOCKET_ERROR)
	{
		printf("send failed\n");
		return 1;
	}

	return 0;
}

void* Networking::Socket::get_in_addr(sockaddr* sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
