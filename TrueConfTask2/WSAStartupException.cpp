#include "WSAStartupException.h"


WSAStartupException::WSAStartupException(int err) :MyTCPException()
{
	switch (err) {
	case WSASYSNOTREADY: this->report = "Error WSAStartup: The underlying network subsystem is not ready for network communication."; break;
	case WSAVERNOTSUPPORTED: this->report = "Error WSAStartup: The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation."; break;
	case WSAEINPROGRESS: this->report = "Error WSAStartup: A blocking Windows Sockets 1.1 operation is in progress."; break;
	case WSAEPROCLIM: this->report = "Error WSAStartup: A limit on the number of tasks supported by the Windows Sockets implementation has been reached."; break;
	case WSAEFAULT: this->report = "Error WSAStartup: The lpWSAData parameter is not a valid pointer."; break;
	}
}


WSAStartupException::~WSAStartupException()
{
}
