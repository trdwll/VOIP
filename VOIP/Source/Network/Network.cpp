#include "voippch.h"
#include "Network/Network.h"

namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	TCPNetwork::TCPNetwork()
	{

	}

	TCPNetwork::TCPNetwork(const std::string& host, uint16 port) :
		m_host(host),
		m_port(port)
	{

	}

	TCPNetwork::~TCPNetwork()
	{

	}

#if VOIP_PLATFORM_WINDOWS

	//struct sockaddr_in TCPNetwork::GetHostAsSockAddr() const
	//{
	//	char len[INET_ADDRSTRLEN];

	//	inet_pton(AF_INET, m_host.c_str(), len);

	//	inet_ntop(AF_INET, &(m_hostsocket.sin_addr), len, INET_ADDRSTRLEN);

	//	return m_hostsocket;
	//	/*in_addr host;

	//	inet_pton(AF_INET, m_host.c_str(), &host);

	//	return ((sockaddr_in)m_hostsocket);*/
	//}

#endif

	void TCPNetwork::SetHost(const std::string& host)
	{
		m_host = host;
	}

	void TCPNetwork::SetPort(uint16 port)
	{
		if (port > 25565 || port == 0) return;

		m_port = port;
	}

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	UDPNetwork::UDPNetwork()
	{

	}

	UDPNetwork::UDPNetwork(const std::string& host, uint16 port) :
		m_host(host),
		m_port(port)
	{

	}

	UDPNetwork::~UDPNetwork()
	{

	}

	void UDPNetwork::SetHost(const std::string& host)
	{
		m_host = host;
	}

	void UDPNetwork::SetPort(uint16 port)
	{
		m_port = port;
	}

}

