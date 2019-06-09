#include "voippch.h"
#include "Network/Platform/Windows/WindowsServerNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	WindowsServerTCPNetwork::WindowsServerTCPNetwork()
	{

	}

	WindowsServerTCPNetwork::~WindowsServerTCPNetwork()
	{

	}

	bool WindowsServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		Disconnect();

		return true;
	}

	void WindowsServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void WindowsServerTCPNetwork::SendChatMessage(const std::string& Message)
	{

	}

	bool WindowsServerTCPNetwork::Init()
	{
		return false;
	}

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	WindowsServerUDPNetwork::WindowsServerUDPNetwork()
	{

	}

	WindowsServerUDPNetwork::~WindowsServerUDPNetwork()
	{

	}

	bool WindowsServerUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void WindowsServerUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	bool WindowsServerUDPNetwork::Init()
	{
		return false;
	}

}