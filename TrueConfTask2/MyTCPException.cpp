#include "MyTCPException.h"

MyTCPException::MyTCPException(char * rep)
{
	this->report = rep;
}

char* MyTCPException::getReport() {
	return this->report;
}

MyTCPException::~MyTCPException()
{
}

