#include "voippch.h"
#include "Network/Platform/Linux/LinuxServerNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	LinuxServerTCPNetwork::LinuxServerTCPNetwork()
	{

	}

	LinuxServerTCPNetwork::~LinuxServerTCPNetwork()
	{

	}

	void LinuxServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void LinuxServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void LinuxServerTCPNetwork::SendChatMessage(char* Message)
	{

	}

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	LinuxServerUDPNetwork::LinuxServerUDPNetwork()
	{

	}

	LinuxServerUDPNetwork::~LinuxServerUDPNetwork()
	{

	}

	void LinuxServerUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void LinuxServerUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

}