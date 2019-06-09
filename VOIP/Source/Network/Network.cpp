#include "voippch.h"
#include "Network/Network.h"

#include "Network/ClientNetwork.h"
#include "Network/ServerNetwork.h"

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
		if (port > 25565 || port == 0)
		{
			m_port = 10005;
		}

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
		if (port > 25565 || port == 0)
		{
			m_port = 10005;
		}

		m_port = port;
	}

	/************************************************************************/
	/* Networking                                                           */
	/************************************************************************/

	ServerTCPNetwork* Network::CreateServerTCPNetwork()
	{
		return nullptr;
	}

	ServerUDPNetwork* Network::CreateServerUDPNetwork()
	{
		return nullptr;
	}

	ClientTCPNetwork* Network::CreateClientTCPNetwork()
	{
		return nullptr;
	}

	ClientUDPNetwork* Network::CreateClientUDPNetwork()
	{
		return nullptr;
	}


}

