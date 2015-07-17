#pragma once
#include "MyTCP.h"

#include "BindException.h"
#include "ListenException.h"
#include "AcceptException.h"
#include "SocketOptionException.h"

class MyTCPServer :
	public MyTCP
{
	const char on = 1;
	SOCKET clientSock;
	sockaddr_in clientAddress;
	int sizeStruct;
public:
	MyTCPServer() :MyTCP() {}
	MyTCPServer(const char *, const char *);
	void myTCPOpen(const char *, const char *);
	void myTCPWait();
	unsigned int myTCPRecieve(char*, unsigned int);
	unsigned int myTCPSend(const char*, unsigned int);
	void myTCPClose();

	SOCKET myTCPWaitWrite(int);
	SOCKET myTCPWaitRead(int);

	const char* getClientIP(char *, u_int);
	u_short getClientPort();
	~MyTCPServer();
};

