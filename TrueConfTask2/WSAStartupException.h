#pragma once
#include "MyTCPException.h"
class WSAStartupException :
	public MyTCPException
{
public:
	WSAStartupException(int err);
	~WSAStartupException();
};

