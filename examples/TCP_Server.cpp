/*
EXAMPLE TCP SERVER
	uses ipv4 to recieve messages from clients on port 3591
	prints out message received from client and ip i.e.

		192.168.20.112: hello world
*/

#include <iostream>

#include "../Wrapper/Sockets.h"

using namespace Networking;

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
	if(argc < 3)
    {
        cout << "missing parameters port and client ip" << endl;
        exit(1);
    }

    const char* PORT = argv[1];
	const char* ip_const = argv[2];
    char CLIENT_IP[INET6_ADDRSTRLEN];
    for(int i=0;i<strlen(ip_const);++i)
    {
        CLIENT_IP[i] = ip_const[i];
    }

    sockinfo sInfo(PORT, 0);

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_STREAM, IPPROTO_TCP, AI_PASSIVE);
	socket.Bind(sock);
	socket.Listen(sock);

	while (true)
	{
		socket.Accept(sock);

		sockinfo sClientInfo(PORT, CLIENT_IP);
		std::string msg = socket.TCPRecv(sock, sClientInfo);

		printf("%s: %s", sClientInfo.ip, msg);
	}

	socket.CloseSock(sock);

    return 0;
}