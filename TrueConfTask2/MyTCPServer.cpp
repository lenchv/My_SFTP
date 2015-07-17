#include "MyTCPServer.h"

MyTCPServer::MyTCPServer(const char *ip, const char *port) :MyTCP() {
	this->myTCPOpen(ip, port);
}

/*************************************************************/
/*����� ������������� ������ �� �������������		         */
/*************************************************************/
void MyTCPServer::myTCPOpen(const char *ip, const char *port)
throw (	SocketOptionException, BindException, ListenException, 
		HostByNameException, InetPtonException, MyTCPException)
{
	int err;
	MyTCP::myTCPOpen(ip, port);
	err=setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if (err == SOCKET_ERROR) throw SocketOptionException(WSAGetLastError());
	err = bind(this->sock, (SOCKADDR *) &this->address, sizeof(this->address));
	if (err == SOCKET_ERROR) throw BindException(WSAGetLastError());
	err = listen(this->sock, SOMAXCONN);
	if (err == SOCKET_ERROR) throw ListenException(WSAGetLastError());
}

/*************************************************************/
/*				�������� ����������� ������������	         */
/*************************************************************/
void MyTCPServer::myTCPWait() 
throw (AcceptException)
{
	this->sizeStruct = sizeof(this->clientAddress);
	this->clientSock = accept(this->sock, (SOCKADDR *)&this->clientAddress, &this->sizeStruct);
	if (this->clientSock == INVALID_SOCKET) throw AcceptException(WSAGetLastError());
}

/*************************************************************/
/*����� �� ��� ���, ���� �� ����� ������� ��� ������         */
/*************************************************************/
unsigned int MyTCPServer::myTCPRecieve(char *buffer, unsigned int length)
throw (RecieveException)
{
	unsigned int recvLen;
	int count;
	count = length;
	while (count > 0)
	{
		recvLen = recv(this->clientSock, buffer, length, 0);
		if (recvLen == SOCKET_ERROR) {
			throw RecieveException(WSAGetLastError());
		}
		if (recvLen == 0) /* ����� �����?  */
			return length - count; /* ������� �������� �������.  */
		buffer += recvLen;
		count -= recvLen;
	}
	return length;
}

/*************************************************************/
/*				�������� ������						         */
/*************************************************************/
unsigned int MyTCPServer::myTCPSend(const char *buffer, unsigned int length)
throw (SendException)
{
	int sendLen = send(this->clientSock, buffer, length, 0);
	if (sendLen == SOCKET_ERROR) {
		throw SendException(WSAGetLastError());
	}
	return sendLen;
}

/*************************************************************/
/*				�������� �� ������					         */
/*************************************************************/
SOCKET MyTCPServer::myTCPWaitWrite(int time) {
	SOCKET s;
	fd_set set;
	timeval t;
	FD_ZERO(&set);
	FD_SET(this->clientSock, &set);
	t.tv_sec = time;
	t.tv_usec = 0;
	s = select(this->clientSock + 1, NULL, &set, NULL, &t);
	return s;
}

/*************************************************************/
/*				�������� �� ������					         */
/*************************************************************/
SOCKET MyTCPServer::myTCPWaitRead(int time) {
	SOCKET s;
	fd_set set;
	timeval t;
	FD_ZERO(&set);
	FD_SET(this->clientSock, &set);
	t.tv_sec = time;
	t.tv_usec = 10;
	s = select(this->clientSock + 1, &set, NULL, NULL, &t);
	return s;
}

/*************************************************************/
/*�������� ������� �������, � ����� � �������		        */
/*************************************************************/
void MyTCPServer::myTCPClose() 
throw (CloseSocketException)
{
	int err = closesocket(this->clientSock);
	if (err == SOCKET_ERROR) throw CloseSocketException(WSAGetLastError());
	MyTCP::myTCPClose();
}

/*************************************************************/
/*      ���������� IP ����� ������� � ��������� ����         */
/*************************************************************/
const char* MyTCPServer::getClientIP(char * str, u_int len) {
	inet_ntop(AF_INET, &this->clientAddress.sin_addr, str, len);
	return str;
}

/*************************************************************/
/*				���������� ���� ������� � ��������� ����     */
/*************************************************************/
u_short MyTCPServer::getClientPort() {
	return ntohs(this->clientAddress.sin_port);
}

MyTCPServer::~MyTCPServer()
{
	try {
		MyTCPServer::myTCPClose();
	}
	catch (CloseSocketException) {}
	catch (WSACleanupException) {}
}
