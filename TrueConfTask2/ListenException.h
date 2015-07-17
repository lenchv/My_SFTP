#pragma once
#include "MyTCPException.h"
class ListenException :
	public MyTCPException
{
public:
	ListenException(int);
	~ListenException();
};

