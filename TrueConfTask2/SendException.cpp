#include "SendException.h"


SendException::SendException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAEACCES: this->report = "The requested address is a broadcast address, but the appropriate flag was not set.Call setsockopt with the SO_BROADCAST socket option to enable use of the broadcast address."; break;
	case WSAEINTR: this->report = "A blocking Windows Sockets 1.1 call was canceled through WSACancelBlockingCall."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAEFAULT: this->report = "The buf parameter is not completely contained in a valid part of the user address space."; break;
	case WSAENETRESET: this->report = "The connection has been broken due to the keep - alive activity detecting a failure while the operation was in progress."; break;
	case WSAENOBUFS: this->report = "No buffer space is available."; break;
	case WSAENOTCONN: this->report = "The socket is not connected."; break;
	case WSAENOTSOCK: this->report = "The descriptor is not a socket."; break;
	case WSAEOPNOTSUPP: this->report = "MSG_OOB was specified, but the socket is not stream - style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only receive operations."; break;
	case WSAESHUTDOWN: this->report = "The socket has been shut down; it is not possible to send on a socket after shutdown has been invoked with how set to SD_SEND or SD_BOTH."; break;
	case WSAEWOULDBLOCK: this->report = "The socket is marked as nonblocking and the requested operation would block."; break;
	case WSAEMSGSIZE: this->report = "The socket is message oriented, and the message is larger than the maximum supported by the underlying transport."; break;
	case WSAEHOSTUNREACH: this->report = "The remote host cannot be reached from this host at this time."; break;
	case WSAEINVAL: this->report = "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled."; break;
	case WSAECONNABORTED: this->report = "The virtual circuit was terminated due to a time - out or other failure.The application should close the socket as it is no longer usable."; break;
	case WSAECONNRESET: this->report = "The virtual circuit was reset by the remote side executing a hard or abortive close.For UDP sockets, the remote host was unable to deliver a previously sent UDP datagram and responded with a 'Port Unreachable' ICMP packet.The application should close the socket as it is no longer usable."; break;
	case WSAETIMEDOUT: this->report = "The connection has been dropped, because of a network failure or because the system on the other end went down without notice."; break;
	}
}


SendException::~SendException()
{
}
