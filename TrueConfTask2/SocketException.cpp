#include "SocketException.h"


SocketException::SocketException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem or the associated service provider has failed."; break;
	case WSAEAFNOSUPPORT: this->report = "The specified address family is not supported.For example, an application tried to create a socket for the AF_IRDA address family but an infrared adapter and device driver is not installed on the local computer."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEMFILE: this->report = "No more socket descriptors are available."; break;
	case WSAEINVAL: this->report = "An invalid argument was supplied.This error is returned if the af parameter is set to AF_UNSPEC and the type and protocol parameter are unspecified."; break;
	case WSAEINVALIDPROVIDER: this->report = "The service provider returned a version other than 2.2."; break;
	case WSAEINVALIDPROCTABLE: this->report = "The service provider returned an invalid or incomplete procedure table to the WSPStartup."; break;
	case WSAENOBUFS: this->report = "No buffer space is available.The socket cannot be created."; break;
	case WSAEPROTONOSUPPORT: this->report = "The specified protocol is not supported."; break;
	case WSAEPROTOTYPE: this->report = "The specified protocol is the wrong type for this socket."; break;
	case WSAEPROVIDERFAILEDINIT: this->report = "The service provider failed to initialize.This error is returned if a layered service provider(LSP) or namespace provider was improperly installed or the provider fails to operate correctly."; break;
	case WSAESOCKTNOSUPPORT: this->report = "The specified socket type is not supported in this address family."; break;
	}
}

SocketException::~SocketException()
{
}
