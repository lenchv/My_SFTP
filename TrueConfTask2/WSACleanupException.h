#pragma once
#include "MyTCPException.h"
class WSACleanupException :
	public MyTCPException
{
public:
	WSACleanupException(int);
	~WSACleanupException();
};

