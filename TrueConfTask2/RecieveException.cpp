#include "RecieveException.h"


RecieveException::RecieveException(int err)
{
	switch (err) {
	case WSANOTINITIALISED: this->report = "A successful WSAStartup call must occur before using this function."; break;
	case WSAENETDOWN: this->report = "The network subsystem has failed."; break;
	case WSAEFAULT: this->report = "The buf parameter is not completely contained in a valid part of the user address space."; break;
	case WSAENOTCONN: this->report = "The socket is not connected."; break;
	case WSAEINTR: this->report = "The(blocking) call was canceled through WSACancelBlockingCall."; break;
	case WSAEINPROGRESS: this->report = "A blocking Windows Sockets 1.1 call is in progress, or the service provider is still processing a callback function."; break;
	case WSAENETRESET: this->report = "For a connection - oriented socket, this error indicates that the connection has been broken due to keep - alive activity that detected a failure while the operation was in progress.For a datagram socket, this error indicates that the time to live has expired."; break;
	case WSAENOTSOCK: this->report = "The descriptor is not a socket."; break;
	case WSAEOPNOTSUPP: this->report = "MSG_OOB was specified, but the socket is not stream - style such as type SOCK_STREAM, OOB data is not supported in the communication domain associated with this socket, or the socket is unidirectional and supports only send operations."; break;
	case WSAESHUTDOWN: this->report = "The socket has been shut down; it is not possible to receive on a socket after shutdown has been invoked with how set to SD_RECEIVE or SD_BOTH."; break;
	case WSAEWOULDBLOCK: this->report = "The socket is marked as nonblocking and the receive operation would block."; break;
	case WSAEMSGSIZE: this->report = "The message was too large to fit into the specified buffer and was truncated."; break;
	case WSAEINVAL: this->report = "The socket has not been bound with bind, or an unknown flag was specified, or MSG_OOB was specified for a socket with SO_OOBINLINE enabled or(for byte stream sockets only) len was zero or negative."; break;
	case WSAECONNABORTED: this->report = "The virtual circuit was terminated due to a time - out or other failure.The application should close the socket as it is no longer usable."; break;
	case WSAETIMEDOUT: this->report = "The connection has been dropped because of a network failure or because the peer system failed to respond."; break;
	case WSAECONNRESET: this->report = "The virtual circuit was reset by the remote side executing a hard or abortive close.The application should close the socket as it is no longer usable.On a UDP - datagram socket, this error would indicate that a previous send operation resulted in an ICMP 'Port Unreachable' message."; break;
	}	
}

RecieveException::~RecieveException()
{
}
