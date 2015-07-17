#include <WinSock2.h>
#include <WS2tcpip.h>

#include "MyTCPException.h"
#include "SocketException.h"
#include "RecieveException.h"
#include "SendException.h"
#include "WSAStartupException.h"
#include "CloseSocketException.h"
#include "WSACleanupException.h"
#include "InetPtonException.h"
#include "HostByNameException.h"

using namespace std;
#pragma once
#pragma comment(lib, "ws2_32.lib")
class MyTCP
{
protected:
	sockaddr_in address;
	SOCKET sock;
public:
	MyTCP();
	MyTCP(const char*, const char*);
	void myTCPOpen(const char*, const char*);
	int myTCPRecieve(void*, unsigned int);
	int myTCPSend(const void*, unsigned int);
	void myTCPClose();

	SOCKET myTCPWaitWrite(int);
	SOCKET myTCPWaitRead(int);

	const char *getIP(char *, u_int);
	u_short getPort();
	virtual ~MyTCP();
};

