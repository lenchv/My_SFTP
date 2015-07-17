#include "MyFTP.h"
#include "MyTCPServer.h"

#include <fstream>

using namespace std;
#pragma once
class MyFTPServer : 
	public MyFTP
{
	MyTCPServer *server;
	char *directory = ".\\";
public:
	MyFTPServer();
	MyFTPServer(const char*);
	MyFTPServer(const char *, const char *);
	void connect();
	void connect(const char *, const char *);
	void recieveFile();

	void setDirectory(const char *);
	const char * getDirectory();
	const char * getClientInfo();
	~MyFTPServer();
private:
	char * strcat_reverse(char *src, const char *dst);
};