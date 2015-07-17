#pragma once
#include "MyTCPException.h"
class SocketException :
	public MyTCPException
{
public:
	SocketException(int);
	~SocketException();
};

