#include "AcceptException.h"


AcceptException::AcceptException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAECONNRESET: this->report = "An incoming connection was indicated, but was subsequently terminated by the remote peer prior to accepting the call."; break;
	case WSAEFAULT: this->report = "The addrlen parameter is too small or addr is not a valid part of the user address space."; break;
	case WSAEINTR: this->report = "A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall."; break;
	case WSAEINVAL: this->report = "The listen function was not invoked prior to accept."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEMFILE: this->report = "The queue is nonempty upon entry to accept and there are no descriptors available."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAENOBUFS: this->report = "No buffer space is available."; break;
	case WSAENOTSOCK: this->report = "The descriptor is not a socket."; break;
	case WSAEOPNOTSUPP: this->report = "The referenced socket is not a type that supports connection - oriented service."; break;
	case WSAEWOULDBLOCK: this->report = "The socket is marked as nonblocking and no connections are present to be accepted."; break;
	}		
}


AcceptException::~AcceptException()
{
}
