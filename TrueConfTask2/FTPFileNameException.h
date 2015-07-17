#pragma once
#include "MyFTPException.h"
class FTPFileNameException :
	public MyFTPException
{
public:
	FTPFileNameException();
	FTPFileNameException(char *err):MyFTPException(err) {}
	~FTPFileNameException();
};

