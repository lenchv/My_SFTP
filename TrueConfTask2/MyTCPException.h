#include <ostream>
#include <winsock2.h>
using namespace std;
#pragma once

class MyTCPException
{
protected:
	char *report;
public:
	MyTCPException(){}
	MyTCPException(char *);
	char *getReport();
	friend ostream& operator << (ostream&, MyTCPException&);
	~MyTCPException();
};

inline ostream& operator<<(ostream &os, MyTCPException &ex) {
	os << ex.getReport()<<endl;
	return os;
}