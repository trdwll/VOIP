#include "voippch.h"
#include "Network/Network.h"

#include "Network/ClientNetwork.h"
#include "Network/ServerNetwork.h"

#ifdef VOIP_PLATFORM_WINDOWS
#include "Network/Platform//Windows/WindowsClientNetwork.h"
#include "Network/Platform//Windows/WindowsServerNetwork.h"
#endif

namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	Network::Network()
	{

	}

	Network::Network(const std::string& host, uint16 port) :
		m_host(host),
		m_port(port)
	{

	}

	Network::~Network()
	{

	}

	void Network::SetHost(const std::string& host)
	{
		m_host = host;
	}

	void Network::SetPort(uint16 port)
	{
		if (port > 25565 || port == 0)
		{
			m_port = 10005;
		}

		m_port = port;
	}

	ServerTCPNetwork* Network::CreateServerTCPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsServerTCPNetwork();
#endif
		return nullptr;
	}

	ServerUDPNetwork* Network::CreateServerUDPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsServerUDPNetwork();
#endif
		return nullptr;
	}

	ClientTCPNetwork* Network::CreateClientTCPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsClientTCPNetwork();
#endif
		return nullptr;
	}

	ClientUDPNetwork* Network::CreateClientUDPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsClientUDPNetwork();
#endif
		return nullptr;
	}


}

