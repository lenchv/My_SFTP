#include "CloseSocketException.h"


CloseSocketException::CloseSocketException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAENOTSOCK: this->report = "The descriptor is not a socket."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEINTR: this->report = "The(blocking) Windows Socket 1.1 call was canceled through WSACancelBlockingCall."; break;
	case WSAEWOULDBLOCK: this->report = "The socket is marked as nonblocking, but the l_onoff member of the linger structure is set to nonzero and the l_linger member of the linger structure is set to a nonzero timeout value."; break;
	}
	
		
		
		
		
		
		
}


CloseSocketException::~CloseSocketException()
{
}
