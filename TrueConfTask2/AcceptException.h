#pragma once
#include "MyTCPException.h"
class AcceptException :
	public MyTCPException
{
public:
	AcceptException(int);
	~AcceptException();
};

