#pragma once
#include "MyTCPException.h"
class SendException :
	public MyTCPException
{
public:
	SendException(int);
	SendException(char *err) :MyTCPException(err){}
	~SendException();
};

