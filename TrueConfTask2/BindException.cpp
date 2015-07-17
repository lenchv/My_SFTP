#include "BindException.h"


BindException::BindException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAEACCES: this->report = "An attempt was made to access a socket in a way forbidden by its access permissions."; break;
	case WSAEADDRINUSE: this->report = "Only one usage of each socket address(protocol / network address / port) is normally permitted."; break;
	case WSAEADDRNOTAVAIL: this->report = "The requested address is not valid in its context."; break;
	case WSAEFAULT: this->report = "The system detected an invalid pointer address in attempting to use a pointer argument in a call."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEINVAL: this->report = "An invalid argument was supplied."; break;
	case WSAENOBUFS: this->report = "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full."; break;
	case WSAENOTSOCK: this->report = "An operation was attempted on something that is not a socket."; break;
	}
}


BindException::~BindException()
{
}
