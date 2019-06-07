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

	void TCPNetwork::SetHost(const std::string& host)
	{
		m_host = host;
	}

	void TCPNetwork::SetPort(uint16 port)
	{
		if (port > 25565 || port == 0) return;

		m_port = port;
	}

	void TCPNetwork::Connect()
	{
		VOIP_CORE_INFO("Connecting to {0}:{1}", m_host, m_port);
	}

	void TCPNetwork::Disconnect()
	{
		VOIP_CORE_INFO("Disconnecting from {0}:{1}", m_host, m_port);
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

	void UDPNetwork::Connect()
	{

	}

	void UDPNetwork::Disconnect()
	{

	}

}

