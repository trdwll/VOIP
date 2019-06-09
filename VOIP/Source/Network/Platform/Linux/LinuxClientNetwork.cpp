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
		VOIP_CLIENT_INFO("LINUX:TCP: Connecting to {0}:{1}", m_host, m_port);
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
		VOIP_CLIENT_INFO("LINUX:TCP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("LINUX:TCP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void LinuxClientTCPNetwork::SendChatMessage(char* Message)
	{
		//if (m_ConnectionStatus == EConnectionStatus::CS_CONNECTED)
		{

		}
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
		VOIP_CLIENT_INFO("LINUX:UDP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("LINUX:UDP: Connected");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void LinuxClientUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("LINUX:UDP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("LINUX:UDP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

}