#include "voippch.h"
#include "Network/Platform/Linux/LinuxClientNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	LinuxClientTCPNetwork::LinuxClientTCPNetwork()
	{

	}

	LinuxClientTCPNetwork::~LinuxClientTCPNetwork()
	{

	}

	void LinuxClientTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		if (m_host.empty() || m_port == 0)
		{
			VOIP_CORE_ERROR("Host or port haven't been set.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return;
		}


		Disconnect();
	}

	void LinuxClientTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("TCP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void LinuxClientTCPNetwork::SendChatMessage(char* Message)
	{
		//if (m_ConnectionStatus == EConnectionStatus::CS_CONNECTED)
		{

		}
	}

	void LinuxClientTCPNetwork::SetClientUsername(std::string Username)
	{
		m_ClientUsername = Username;
	}

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	LinuxClientUDPNetwork::LinuxClientUDPNetwork()
	{

	}

	LinuxClientUDPNetwork::~LinuxClientUDPNetwork()
	{

	}

	void LinuxClientUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Connected");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void LinuxClientUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

}