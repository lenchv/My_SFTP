#pragma once
#include "MyTCPException.h"
class BindException :
	public MyTCPException
{
public:
	BindException(int);
	~BindException();
};

