#include "MyFTPClient.h"

/*************************************************************/
/***********����������� �� ���������**************************/
/*************************************************************/
MyFTPClient::MyFTPClient() :MyFTP()
{
	this->host = new MyTCPClient();
}
/*************************************************************/
/***********����������� c ������ ����� �� �����***************/
/*************************************************************/
MyFTPClient::MyFTPClient(const char *fileName) :MyFTPClient() {
	this->setFile(fileName);
}
/*************************************************************/
/*������� ��������� ����, �������� �� �������������� ����
��� �����, ��������� ��� � ���� ������, � ���������� ������ �����*/
/*************************************************************/
void MyFTPClient::setFile(const char *fileName) {
	int j = 0;
	file.open(fileName, ios::in | ios::binary);
	this->fileName = new char[256];
	for (int i = 0; i < 255; i++) {
		this->fileName[j++] = fileName[i];
		if (fileName[i] == '\\' || fileName[i] == '/') j = 0;
		if (fileName[i] == '\0') {
			break;
		}
	}
	file.seekg(0, ios::end);
	this->fileLength = (unsigned long)file.tellg();
	file.seekg(0, ios::beg);
}

/*************************************************************/
/***********����������� � �������*****************************/
/*************************************************************/
void MyFTPClient::connect(const char *ip, const char *port) 
throw(ConnectException, HostByNameException, InetPtonException, MyTCPException)
{
	this->host->myTCPOpen(ip, port);
}
/*************************************************************/
/***********�������� �����************************************/
/*************************************************************/
void MyFTPClient::sendFile()
throw (FTPFileNameException, SendException)
{
	if (file.is_open()) {
		char msg[8];	//��������� �� �������
		int rc;
		char *buf = new char[this->packageSize];  //������ ��� ��������
		this->size = 0;
		unsigned int countPackage = (unsigned int)(this->fileLength / (unsigned long)this->packageSize); //���������� ������������ �������
		unsigned short countEndBytes = (unsigned short)(this->fileLength % (unsigned long)this->packageSize); //���������� ���������� ����, �� ������� ������� ������
		file.seekg(0, ios::beg);
		struct header {
			unsigned long length;
			char name[256];
		} head;
		head.length = htonl(this->fileLength);
		strcpy(head.name, this->fileName);
		
		try {
			try {
				this->host->myTCPSend((char *)&head, sizeof(head));
				this->host->myTCPRecieve(msg, sizeof(msg)); //OK
			}
			catch (RecieveException ex) {
				this->closeConnection = true;
				throw SendException(ex.getReport());
			}
			catch (SendException ex) {
				this->closeConnection = true;
				throw SendException(ex.getReport());
			}
			
			for (unsigned int i = 0; i < countPackage; i++) {
				this->file.seekg(i*this->packageSize, ios::beg);
				this->file.read(buf, this->packageSize);
				rc = this->host->myTCPWaitWrite(60);
				if (rc == 0) {
					this->closeConnection = true;
					throw MyTCPException("Fail of connection! Error send data!");
				}
				try {
					rc = this->host->myTCPSend(buf, this->packageSize);
					this->size += rc;
					this->host->myTCPRecieve(msg, sizeof(msg)); //OK
				}
				catch (RecieveException ex) {
					this->closeConnection = true;
					throw SendException(ex.getReport());
				}
				catch (SendException ex) {
					this->closeConnection = true;
					throw SendException(ex.getReport());
				}
			
				if (rc != this->packageSize) {
					this->closeConnection = true;
					throw MyTCPException("Error send file!");
				}
			}
			if (countEndBytes) {
				this->file.read(buf, countEndBytes);
				rc = this->host->myTCPWaitWrite(30);
				if (rc == 0) {
					this->closeConnection = true;
					throw MyTCPException("Fail of connection! Error send data!");
				}
				try {
					rc = this->host->myTCPSend(buf, countEndBytes);
					this->size += rc;
					this->host->myTCPRecieve(msg, sizeof(msg));
				}
				catch (RecieveException ex) {
					this->closeConnection = true;
					throw SendException(ex.getReport());
				}
				catch (SendException ex) {
					this->closeConnection = true;
					throw SendException(ex.getReport());
				}
			}
		}
		catch (SendException ex) {
			delete[] buf;
			throw SendException(ex.getReport());
		}
		delete[] buf;
	}
	else {
		this->closeConnection = true;
		throw FTPFileNameException("Error open file!");
	}
}
/*************************************************************/
/***********�������� ����� � �������� ����� �����*************/
/*************************************************************/
void MyFTPClient::sendFile(const char *fileName){
	this->setFile(fileName);
	this->sendFile();
}

MyFTPClient::~MyFTPClient()
{
	this->closeConnection = true;
	this->host->myTCPClose();
	delete this->host;
	delete[] this->fileName;
	if (file) file.close();
}
