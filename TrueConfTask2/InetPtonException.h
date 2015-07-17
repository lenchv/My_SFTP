#pragma once
#include "MyTCPException.h"
class InetPtonException :
	public MyTCPException
{
public:
	InetPtonException();
	InetPtonException(char * err) :MyTCPException(err) {}
	~InetPtonException();
};

