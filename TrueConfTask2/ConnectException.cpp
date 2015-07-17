#include "ConnectException.h"


ConnectException::ConnectException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "Error Connect: A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "Error Connect: The network subsystem has failed."; break;
	case WSAEADDRINUSE: this->report = "Error Connect: The socket's local address is already in use and the socket was not marked to allow\
address reuse with SO_REUSEADDR. This error usually occurs when executing bind,\
but could be delayed until the connect function if the bind was to a wildcard\
address (INADDR_ANY or in6addr_any) for the local IP address.\
A specific address needs to be implicitly bound by the connect function."; break;
	case WSAEINTR: this->report = "Error Connect: The blocking Windows Socket 1.1 call was canceled through WSACancelBlockingCall."; break;
	case WSAEINPROGRESS: this->report = "Error Connect: A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEALREADY: this->report = "Error Connect: A nonblocking connect call is in progress on the specified socket."; break;
	case WSAEADDRNOTAVAIL: this->report = "Error Connect: The remote address is not a valid address(such as INADDR_ANY or in6addr_any) ."; break;
	case WSAEAFNOSUPPORT: this->report = "Error Connect: Addresses in the specified family cannot be used with this socket."; break;
	case WSAECONNREFUSED: this->report = "Error Connect: The attempt to connect was forcefully rejected."; break;
	case WSAEFAULT: this->report = "Error Connect: The sockaddr structure pointed to by the name contains incorrect address format for the \
associated address family or the namelen parameter is too small.This error is also returned \
if the sockaddr structure pointed to by the name parameter with a length specified in the \
namelen parameter is not in a valid part of the user address space."; break;
	case WSAEINVAL: this->report = "Error Connect: The parameter 'socket' is a listening socket."; break;
	case WSAEISCONN: this->report = "Error Connect: The socket is already connected(connection - oriented sockets only)."; break;
	case WSAENETUNREACH: this->report = "Error Connect: The network cannot be reached from this host at this time.."; break;
	case WSAEHOSTUNREACH: this->report = "Error Connect: A socket operation was attempted to an unreachable host."; break;
	case WSAENOBUFS: this->report = "Error Connect: No buffer space is available.The socket cannot be connected."; break;
	case WSAENOTSOCK: this->report = "Error Connect: The descriptor specified in the s parameter is not a socket."; break;
	case WSAETIMEDOUT: this->report = "Error Connect: An attempt to connect timed out without establishing a connection."; break;
	case WSAEWOULDBLOCK: this->report = "Error Connect: The socket is marked as nonblocking and the connection cannot be completed immediately."; break;
	case WSAEACCES: this->report = "Error Connect: An attempt to connect a datagram socket to broadcast address failed because setsockopt option SO_BROADCAST is not enabled."; break;
	}
}

ConnectException::~ConnectException()
{
}
