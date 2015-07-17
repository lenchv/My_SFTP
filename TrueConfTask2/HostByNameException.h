#pragma once
#include "MyTCPException.h"
class HostByNameException :
	public MyTCPException
{
public:
	HostByNameException();
	HostByNameException(char *err) : MyTCPException(err) {}
	~HostByNameException();
};

