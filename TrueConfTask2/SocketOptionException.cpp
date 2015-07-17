#include "SocketOptionException.h"


SocketOptionException::SocketOptionException()
{
}
SocketOptionException::SocketOptionException(int err)
{
	switch (err) {
	case WSANOTINITIALISED:
		this->report = "A successful WSAStartup call must occur before using this function."; break;
	case 	WSAENETDOWN:
		this->report = "The network subsystem has failed."; break;
	case WSAEFAULT:
		this->report = "The buffer pointed to by the optval parameter is not in a valid part of the process address space or the optlen parameter is too small."; break;
	case WSAEINPROGRESS:
		this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEINVAL:
		this->report = "The level parameter is not valid, or the information in the buffer pointed to by the optval parameter is not valid."; break;
	case WSAENETRESET:
		this->report = "The connection has timed out when SO_KEEPALIVE is set."; break;
	case WSAENOPROTOOPT:
		this->report = "The option is unknown or unsupported for the specified provider or socket(see SO_GROUP_PRIORITY limitations)."; break;
	case WSAENOTCONN:
		this->report = "The connection has been reset when SO_KEEPALIVE is set."; break;
	case WSAENOTSOCK:
		this->report = "The descriptor is not a socket."; break;
	}
}

SocketOptionException::~SocketOptionException()
{
}
