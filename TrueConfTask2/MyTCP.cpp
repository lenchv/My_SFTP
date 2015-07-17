#include "MyTCP.h"
/*************************************************************/
/***********Конструктор по умолчанию**************************/
/*              Открывает соккет                             */
/*************************************************************/
MyTCP::MyTCP()
throw (WSAStartupException, SocketException)
{
	WSADATA ws;
	int err;
	err=WSAStartup(0x0101, &ws);
	if (err) throw WSAStartupException(err);
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->sock == INVALID_SOCKET) throw SocketException(WSAGetLastError());
	ZeroMemory((void *)&this->address, sizeof(this->address));
}

/*************************************************************/
/***********Конструктор **************************************/
/*Открывает соккет и заполняется структура адреса            */
/*************************************************************/
MyTCP::MyTCP(const char *ip, const char *port) :MyTCP() {
	myTCPOpen(ip, port);
}
/*************************************************************/
/*                   Заполняется структура адреса            */
/*************************************************************/
void MyTCP::myTCPOpen(const char *ip, const char *port) 
throw(HostByNameException, InetPtonException, MyTCPException)
{
	IN_ADDR *addr = new IN_ADDR();
	SERVENT *sp; 
	HOSTENT *hp;
	char  *endptr;
	long prt;
	int err;
	this->address.sin_family = AF_INET;;
	if (ip != NULL) {
		if (!(err=inet_pton(AF_INET, ip, addr)))
		{
			hp = gethostbyname(ip);
			if (hp == NULL)
			{
				throw HostByNameException("Uknown host");
			}
			 addr = (IN_ADDR *)hp->h_addr;
		}
		else if (err < 0) {
			throw InetPtonException("Error call inet_pton()");
		}
		this->address.sin_addr = *addr;
	}
	else {
		this->address.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	
	prt = strtol(port, &endptr, 0);
	if (*endptr == '\0') {
		this->address.sin_port = htons((u_short)prt);
	}
	else
	{
		sp = getservbyname(port, "tcp");
		if (sp == NULL) {
			throw MyTCPException("Uknown service");
		}
		this->address.sin_port = sp->s_port;
	}
}
/*************************************************************/
/*							Прием данных		             */
/*************************************************************/
int MyTCP::myTCPRecieve(void *buffer, unsigned int length)
throw (RecieveException)
{
	int recvLen = recv(this->sock, (char *)buffer, length, 0);
	if (recvLen == SOCKET_ERROR) {
		throw RecieveException(WSAGetLastError());
	}
	return recvLen;
}
/*************************************************************/
/*				Передача данных					             */
/*************************************************************/
int MyTCP::myTCPSend(const void *buffer, unsigned int length) 
throw (SendException)
{
	int sendLen = send(this->sock, (char *)buffer, length, 0);
	if (sendLen == SOCKET_ERROR) {
		throw SendException(WSAGetLastError());
	}
	return sendLen;
}
/*************************************************************/
/*				Ожидание освобождения канала на запись       */
/*************************************************************/
SOCKET MyTCP::myTCPWaitWrite(int time) {
	SOCKET s;
	fd_set set;
	timeval t;
	FD_ZERO(&set);
	FD_SET(this->sock, &set);
	t.tv_sec = time;
	t.tv_usec = 0;
	s = select(this->sock + 1, NULL, &set, NULL, &t);
	return s;
}

/*************************************************************/
/*				Ожидание освобождения канала на чтение       */
/*************************************************************/
SOCKET MyTCP::myTCPWaitRead(int time) {
	SOCKET s;
	fd_set set;
	timeval t;
	FD_ZERO(&set);
	FD_SET(this->sock, &set);
	t.tv_sec = time;
	t.tv_usec = 10;
	s = select(this->sock + 1, &set, NULL, NULL, &t);
	return s;
}

/*************************************************************/
/*				Закрытие соккета					         */
/*************************************************************/
void MyTCP::myTCPClose()
throw (CloseSocketException, WSACleanupException)
{
	int err;
	err=closesocket(this->sock);
	if (err == SOCKET_ERROR) throw CloseSocketException(WSAGetLastError());
	err=WSACleanup();
	if (err == SOCKET_ERROR) throw WSACleanupException(WSAGetLastError());
}

/*************************************************************/
/*				Возвращает IP адрес в строковом виде         */
/*************************************************************/
const char* MyTCP::getIP(char *str, u_int len) {
	inet_ntop(AF_INET, &this->address.sin_addr, str, len);
	return str;
}

/*************************************************************/
/*				Возвращает порт в строковом виде	         */
/*************************************************************/
u_short MyTCP::getPort() {
	return ntohs(this->address.sin_port);
}

MyTCP::~MyTCP()
{
	try {
		this->myTCPClose();
	}
	catch (MyTCPException) {}
}
