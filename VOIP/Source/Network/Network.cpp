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
		if (!IsPortValid(port))
		{
			m_port = DEFAULT_PORT;
			return;
		}

		m_port = port;
	}

	bool Network::IsPortValid(uint16 port) const
	{
		return port <= 25565 && port > 0;
	}

	ServerTCPNetwork* Network::CreateServerTCPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsServerTCPNetwork();
#elif VOIP_PLATFORM_LINUX
		return new LinuxServerTCPNetwork();
#endif
		return nullptr;
	}

	ServerUDPNetwork* Network::CreateServerUDPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsServerUDPNetwork();
#elif VOIP_PLATFORM_LINUX
		return new LinuxServerUDPNetwork();
#endif
		return nullptr;
	}

	ClientTCPNetwork* Network::CreateClientTCPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsClientTCPNetwork();
#elif VOIP_PLATFORM_LINUX
		return new LinuxClientTCPNetwork();
#endif
		return nullptr;
	}

	ClientUDPNetwork* Network::CreateClientUDPNetwork()
	{
#ifdef VOIP_PLATFORM_WINDOWS
		return new WindowsClientUDPNetwork();
#elif VOIP_PLATFORM_LINUX
		return new LinuxClientUDPNetwork();
#endif
		return nullptr;
	}


}

