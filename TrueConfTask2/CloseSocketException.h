#pragma once
#include "MyTCPException.h"
class CloseSocketException :
	public MyTCPException
{
public:
	CloseSocketException(int);
	~CloseSocketException();
};

