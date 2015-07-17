#pragma once
#include "MyTCPException.h"
class SocketOptionException :
	public MyTCPException
{
public:
	SocketOptionException();
	SocketOptionException(int);
	~SocketOptionException();
};

