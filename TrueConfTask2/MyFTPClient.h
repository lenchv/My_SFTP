#include "MyFTP.h"
#include "MyTCPClient.h"

using namespace std;
#pragma once
class MyFTPClient: 
	public MyFTP
{
	MyTCPClient *host;
public:
	MyFTPClient();
	MyFTPClient(const char *);
	void connect(const char *, const char *);
	void sendFile();
	void sendFile(const char *);

	void setFile(const char *);
	~MyFTPClient();
};

