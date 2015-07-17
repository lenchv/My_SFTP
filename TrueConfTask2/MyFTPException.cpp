#include "MyFTPException.h"


MyFTPException::MyFTPException()
{
}

MyFTPException::MyFTPException(char * rep)
{
	this->report = rep;
}

char* MyFTPException::getReport() {
	return this->report;
}

MyFTPException::~MyFTPException()
{
}
