#include "voippch.h"
#include "Network/Platform/Mac/MacServerNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	/*MacServerTCPNetwork::MacServerTCPNetwork()
	{

	}

	MacServerTCPNetwork::~MacServerTCPNetwork()
	{

	}

	bool MacServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void MacServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void MacServerTCPNetwork::SendChatMessage(const std::string& Message)
	{

	}

	void MacServerTCPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool MacServerTCPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool MacServerTCPNetwork::Init()
	{
		return false;
	}*/

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	/*MacServerUDPNetwork::MacServerUDPNetwork()
	{

	}

	MacServerUDPNetwork::~MacServerUDPNetwork()
	{

	}

	bool MacServerUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void MacServerUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void MacServerUDPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool MacServerUDPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool MacServerUDPNetwork::Init()
	{
		return false;
	}*/

}