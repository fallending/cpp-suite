#include "tcpSocket.h"

tcpSocket::tcpSocket():
	m_sd(0)
{}

tcpSocket::tcpSocket(int sd):
	m_sd(sd)
{}

unsigned short tcpSocket::getSrcPort()
{
	struct sockaddr_in localAddress;
	socklen_t addressLength = sizeof(localAddress);
	getsockname(m_sd, (struct sockaddr*)&localAddress, &addressLength);
	return ntohs(localAddress.sin_port);
}

string tcpSocket::getSrcHostname()
{
	struct sockaddr_in localAddress;
	socklen_t addressLength = sizeof(localAddress);
	getsockname(m_sd, (struct sockaddr*)&localAddress, &addressLength);
	return string(inet_ntoa( localAddress.sin_addr));
	//return string("127.0.0.1");
}

unsigned short tcpSocket::getDestPort()
{
	struct sockaddr_in localAddress;
	socklen_t addressLength = sizeof(localAddress);
	getpeername(m_sd, (struct sockaddr*)&localAddress, &addressLength);
	return ntohs(localAddress.sin_port);
}

string tcpSocket::getDestHostname()
{
	struct sockaddr_in localAddress;
	socklen_t addressLength = sizeof(localAddress);
	getpeername(m_sd, (struct sockaddr*)&localAddress, &addressLength);
	return string(inet_ntoa( localAddress.sin_addr));
	//return string("127.0.0.1");
}

bool tcpSocket::connect(string hostname, unsigned short port)
{
	stringstream strport;
	strport<<port;

	struct addrinfo hints, *res;

	// first, load up address structs with getaddrinfo():

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(hostname.c_str(), strport.str().c_str(), &hints, &res);

	// make a socket:

	m_sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// connect!

	return ::connect(m_sd, res->ai_addr, res->ai_addrlen) != -1;
}

bool tcpSocket::bind(unsigned short port)
{
	stringstream strport;
	strport<<port;
	struct addrinfo hints, *res;

	// first, load up address structs with getaddrinfo():

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;  // use IPv4 or IPv6, whichever
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;     // fill in my IP for me

	getaddrinfo(NULL, strport.str().c_str(), &hints, &res);

	// make a socket:

	m_sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	// bind it to the port we passed in to getaddrinfo():

	bool success = ::bind(m_sd, res->ai_addr, res->ai_addrlen) != -1;
	return success;
	
}

bool tcpSocket::bind()
{
	return tcpSocket::bind(0);
}

bool tcpSocket::listen()
{
	return ::listen(m_sd, 10) !=-1;
}

tcpSocket tcpSocket::accept()
{
	struct sockaddr_storage their_addr;
	socklen_t addr_size;
	return tcpSocket(::accept(m_sd, (struct sockaddr *)&their_addr, &addr_size));
}

int tcpSocket::sendString(string data)
{
	//if socket is uninitialized
	if (m_sd <= 0)
	{
		return -1;
	}
	
	return send(m_sd, data.c_str(), data.length(), 0);
	
}

int tcpSocket::sendData(char* buffer, int size)
{
	//if socket is uninitialized
	if (m_sd <= 0)
	{
		return -1;
	}
	
	return send(m_sd, buffer, size, 0);
}

string tcpSocket::recvString(int max_bytes)
{
	//if socket is uninitialized
	if (m_sd <= 0)
	{
		return "";
	}
	
	char* buffer = new char[max_bytes];
	
	int bytes_recveived = recv(m_sd, buffer, max_bytes-1, 0);
	buffer[bytes_recveived] = '\0';
	
	return string(buffer);
}

string tcpSocket::recvString()
{
	return recvString(RECV_STR_BUF_SIZE);
}

int tcpSocket::recvData(char* buffer, int size)
{
	//if socket is uninitialized
	if (m_sd <= 0)
	{
		return -1;
	}
	
	return recv(m_sd, buffer, size, 0);
}

void tcpSocket::close()
{
	::close(m_sd);
}
