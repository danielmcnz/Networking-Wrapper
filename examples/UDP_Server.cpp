/* 
EXAMPLE UDP SERVER 
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
	if(argc < 2)
    {
        cout << "missing parameter port" << endl;
        exit(1);
    }

    const char* PORT = argv[1];

    sockinfo sInfo(PORT, 0);

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_DGRAM, IPPROTO_UDP, AI_PASSIVE);
	socket.Bind(sock);

	while (true)
	{
		sockinfo sClientInfo;
		sClientInfo.port = PORT;

		std::string msg = socket.UDPRecv(sock, sClientInfo);

		printf("%s: %s", sClientInfo.ip, msg.c_str());
	}
}