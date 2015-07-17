#pragma once
#include "MyTCPException.h"
class RecieveException :
	public MyTCPException
{
public:
	RecieveException(int);
	RecieveException(char *err) :MyTCPException(err) {}
	~RecieveException();
};

