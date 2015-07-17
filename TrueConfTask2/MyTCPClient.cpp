#include "MyTCPClient.h"


MyTCPClient::MyTCPClient(const char * ip, const char * port) : MyTCP()
{
	this->myTCPOpen(ip, port);
}

/*************************************************************/
/*				Соединение с сервером				         */
/*************************************************************/
void MyTCPClient::myTCPOpen(const char *ip, const char* port) 
throw(ConnectException, HostByNameException, InetPtonException, MyTCPException)
{
	MyTCP::myTCPOpen(ip, port);
	if (connect(this->sock, (SOCKADDR *)&this->address, sizeof(this->address)) == SOCKET_ERROR) {
		throw ConnectException(WSAGetLastError());
	}
}

MyTCPClient::~MyTCPClient()
{
}
