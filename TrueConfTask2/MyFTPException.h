#include <iostream>
using namespace std;
#pragma once
class MyFTPException
{
	char *report;
public:
	MyFTPException();
	MyFTPException(char *);
	char *getReport();
	friend ostream& operator << (ostream&, MyFTPException&);
	~MyFTPException();
};

inline ostream& operator<<(ostream &os, MyFTPException &ex) {
	os << ex.getReport() << endl;
	return os;
}
