#pragma once
#include "MyTCP.h"
#include "ConnectException.h"

class MyTCPClient :
	public MyTCP
{
public:
	MyTCPClient() : MyTCP() {  }
	MyTCPClient(const char*, const char*);
	void myTCPOpen(const char*, const char*);

	~MyTCPClient();
};

