#include <iostream>

#include "../Wrapper/Sockets.h"

using namespace Networking;

using std::cout;
using std::cin;
using std::endl;

int main(int argc, char **argv)
{
	if(argc < 3)
    {
        cout << "missing parameters port and ip" << endl;
        exit(1);
    }

    const char* PORT = argv[1];
    const char* ip_const = argv[2];
    char IP[INET6_ADDRSTRLEN];
    for(int i=0;i<strlen(ip_const);++i)
    {
        IP[i] = ip_const[i];
    }

    sockinfo sInfo(PORT, IP);

	Socket socket(sInfo);
	SOCKET sock = socket.Sock(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0);
	socket.Connect(sock);

	std::string msg;
	cout << "> ";
	cin >> msg;

	socket.TCPSend(sock, msg);

	socket.CloseSock(sock);

    return 0;
}