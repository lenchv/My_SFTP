#include "ListenException.h"


ListenException::ListenException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEADDRINUSE: this->report = "The socket's local address is already in use and the socket was not marked to allow address reuse with SO_REUSEADDR. This error usually occurs during execution of the bind function, but could be delayed until this function if the bind was to a partially wildcard address (involving ADDR_ANY) and if a specific address needs to be committed at the time of this function."; break;
	case WSAEINVAL: this->report = "The socket has not been bound with bind."; break;
	case WSAEISCONN: this->report = "The socket is already connected."; break;
	case WSAEMFILE: this->report = "No more socket descriptors are available."; break;
	case WSAENOBUFS: this->report = "No buffer space is available."; break;
	case WSAENOTSOCK: this->report = "The descriptor is not a socket."; break;
	case WSAEOPNOTSUPP: this->report = "The referenced socket is not of a type that supports the listen operation."; break;
	}		
}


ListenException::~ListenException()
{
}
