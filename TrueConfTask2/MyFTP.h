#include "MyTCP.h"
#include <fstream>
#include "FTPFileNameException.h"

#pragma once
class MyFTP
{
protected:
	const unsigned short packageSize = 1024;
	fstream file;
	unsigned int fileLength;
	char *fileName;
	unsigned int size = 0;
	bool closeConnection;
public:
	MyFTP() { this->closeConnection = false; }
	unsigned int getSize(){	return this->size; }
	unsigned int getFileLength() { return this->fileLength;	}
	unsigned short getPackageSize() { return this->packageSize; }
	char *getFileName() { return this->fileName; }
	bool isOpenFile() { return this->file.is_open(); }
	bool isClose() { return this->closeConnection; }
	bool setClose(bool cl) { this->closeConnection = cl; }
	virtual ~MyFTP() {}
};