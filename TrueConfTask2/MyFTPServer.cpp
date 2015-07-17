#include "MyFTPServer.h"

/*************************************************************/
/***********Конструктор по умолчанию**************************/
/*************************************************************/
MyFTPServer::MyFTPServer() :MyFTP()
{
	this->server = new MyTCPServer();
}

/*************************************************************/
/***********Конструктор с адресом сервера по умолчанию********/
/*************************************************************/
MyFTPServer::MyFTPServer(const char *port)
throw (SocketOptionException, BindException, ListenException,
HostByNameException, InetPtonException, MyTCPException)
:MyFTP()
{
	this->server = new MyTCPServer(NULL, port);
}

/*************************************************************/
/***Конструктор с адресом и портом задаваемыми пользователем**/
/*************************************************************/
MyFTPServer::MyFTPServer(const char *ip, const char *port) 
throw (SocketOptionException, BindException, ListenException,
HostByNameException, InetPtonException, MyTCPException)
:MyFTP()
{
	this->server = new MyTCPServer(ip, port);
}

/*************************************************************/
/***********Ожидает соединения с клиентом*********************/
/*************************************************************/
void MyFTPServer::connect()
throw (AcceptException)
{
	this->server->myTCPWait();
}

/*************************************************************/
/***********Открывает канал и ждет соединения с клиентом******/
/*************************************************************/
void MyFTPServer::connect(const char *ip, const char *port)
throw (AcceptException, SocketOptionException, BindException, ListenException,
HostByNameException, InetPtonException, MyTCPException)
{
	this->server->myTCPOpen(ip, port);
	this->server->myTCPWait();
}

/*************************************************************/
/***********Прием файла**************************/
/*************************************************************/
void MyFTPServer::recieveFile()
throw (RecieveException, MyTCPException)
{
	int rc;
	unsigned int countPackage; //количество принимаемых пакетов 
	unsigned short countEndBytes;  //количество остаточных байт, если размер файла не кратен размеру пакета
	this->fileName = new char[256];
	try {
		rc = this->server->myTCPRecieve((char *)&this->fileLength, sizeof(unsigned long));//прием длины файла
		rc = this->server->myTCPRecieve(this->fileName, 256); //прием имени файла
	}
	catch (RecieveException ex) {
		this->closeConnection = true;
		throw RecieveException(ex.getReport());
	}
	
	this->fileLength = ntohl(this->fileLength);
	this->fileName=this->strcat_reverse(this->fileName, this->directory); //соединение имени файла с директорией, в которую будет сохранятся файл
	
	//создаем файл
	this->file.open(this->fileName, ios::out | ios::binary | ios::trunc);
	countPackage = (unsigned int)(this->fileLength / (unsigned long)this->packageSize); //количество передаваемых пакетов
	countEndBytes = (unsigned short)(this->fileLength % (unsigned long)this->packageSize); //количество остаточных байт, не кратных размеру пакета

	if (file.is_open()) {
		this->size = 0; 
		char *buf = new char[this->packageSize]; //приемный буффер
		file.seekp(0, ios::beg);
		try {
			this->server->myTCPSend("OK", 3);	//отправка подтверждения об успешном приеме информации о файле и подтверждение приема данных
		}
		catch (SendException ex) {
			this->closeConnection = true;
			throw SendException(ex.getReport());
		}
		for (unsigned int i = 0; i < countPackage; i++) {
			rc = this->server->myTCPWaitRead(60); //Ждем пока сокет будет готов для чтения
			if (rc == 0) {
				this->closeConnection = true;
				throw MyTCPException("Time of wait off, connection close!");
			}
			try {
				//принимаем пакет данных
				rc = this->server->myTCPRecieve(buf, this->packageSize);
			}
			catch (RecieveException ex) {
				this->closeConnection = true;
				throw RecieveException(ex.getReport());
			}
			
			this->size += rc;
			if (rc != this->packageSize) {
				this->closeConnection = true;
				file.close();
				throw RecieveException("Error recieve data!");
			}
			file.write(buf, rc);
			try {
				this->server->myTCPSend("OK", 3); //подтверждаем прием
			}
			catch (SendException ex) {
				this->closeConnection = true;
				throw RecieveException(ex.getReport());
			}
		}
		if (countEndBytes) {
			rc = this->server->myTCPWaitRead(120);
			if (rc == 0) {
				this->closeConnection = true;
				throw MyTCPException("Time wait off, connection close!");
			}
			try {
				rc = this->server->myTCPRecieve(buf, countEndBytes);
			}
			catch (RecieveException ex) {
				this->closeConnection = true;
				throw RecieveException(ex.getReport());
			}
			this->size += rc;
			
			if (rc != countEndBytes) {
				this->closeConnection = true;
				file.close();
				throw RecieveException("Error recieve data!");
			}
			file.write(buf, rc);
			try {
				this->server->myTCPSend("OK", 3);
			}
			catch (SendException ex) {
				this->closeConnection = true;
				throw RecieveException(ex.getReport());
			}
		}
		file.close();

		delete [] buf;
	}
	else {
		this->closeConnection = true;
		throw RecieveException("Error create file!");
	}
}

/*************************************************************/
/***********Установка рабочей директории*******************/
/*************************************************************/
void MyFTPServer::setDirectory(const char *name) {
	this->directory = new char[strlen(name)+2];
	for (int i = 0; i < strlen(name)+1; i++) {
		if (name[i] == '\0') {
			this->directory[i] = '\\';
			this->directory[i+1] = '\0';
			break;
		}
		this->directory[i] = name[i];
		
	}
	
}
/*************************************************************/
/***********Получение рабочей директории*******************/
/*************************************************************/
const char * MyFTPServer::getDirectory() {
	return this->directory;
}
/*************************************************************/
/***********Информация о клиенте*******************/
/*************************************************************/
const char * MyFTPServer::getClientInfo() {
	char *info = new char[32];
	this->server->getClientIP(info, 16);
	int i = 0;
	while (info[i++] != '\0');
	info[i-1] = ':';
	itoa(this->server->getClientPort(), info + i, 10);
	return info;
}

/*************************************************************/
/***********Соединяет dst c src*******************************/
/*************************************************************/
char * MyFTPServer::strcat_reverse(char *src, const char *dst) {
	char * buf = new char[1000];
	int n = 0;
	for (int i = 0; i < 745; i++) {
		if (dst[i] == '\0') {
			n = i;
			break;
		}
		buf[i] = dst[i];
	}
	for (int i = 0; i < 255; i++) {
		buf[n + i] = src[i];
		if (src[i] == '\0') {
			break;
		}
	}
	return buf;
}

MyFTPServer::~MyFTPServer()
{
	this->closeConnection = true;
	this->server->myTCPClose();
	delete this->server;
	delete[] this->fileName;
}
