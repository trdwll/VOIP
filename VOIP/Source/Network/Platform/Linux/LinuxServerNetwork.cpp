#include "voippch.h"
#include "Network/Platform/Linux/LinuxServerNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	/*LinuxServerTCPNetwork::LinuxServerTCPNetwork()
	{

	}

	LinuxServerTCPNetwork::~LinuxServerTCPNetwork()
	{

	}

	bool LinuxServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void LinuxServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void LinuxServerTCPNetwork::SendChatMessage(const std::string& Message)
	{

	}

	void LinuxServerTCPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool LinuxServerTCPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool LinuxServerTCPNetwork::Init()
	{
		return false;
	}*/

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	/*LinuxServerUDPNetwork::LinuxServerUDPNetwork()
	{

	}

	LinuxServerUDPNetwork::~LinuxServerUDPNetwork()
	{

	}

	bool LinuxServerUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void LinuxServerUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void LinuxServerUDPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool LinuxServerUDPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool LinuxServerUDPNetwork::Init()
	{
		return false;
	}*/

}