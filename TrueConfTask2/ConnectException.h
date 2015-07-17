#pragma once
#include "MyTCPException.h"
class ConnectException :
	public MyTCPException
{
public:
	ConnectException(int);
	~ConnectException();
};

