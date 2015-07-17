#include "WSACleanupException.h"


WSACleanupException::WSACleanupException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	}
	
		
		
		
		
		
}


WSACleanupException::~WSACleanupException()
{
}
