#include "voippch.h"
#include "Network/Platform/Mac/MacClientNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	/*MacClientTCPNetwork::MacClientTCPNetwork()
	{

	}

	MacClientTCPNetwork::~MacClientTCPNetwork()
	{

	}

	bool MacClientTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("Mac:TCP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		if (m_host.empty() || m_port == 0)
		{
			VOIP_CORE_ERROR("Host or port haven't been set.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return false;
		}

		VOIP_CLIENT_INFO("Mac:TCP: Connected to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
		return true;
	}

	void MacClientTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("Mac:TCP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("Mac:TCP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void MacClientTCPNetwork::SendChatMessage(const std::string& Message)
	{
		if (m_ConnectionStatus == EConnectionStatus::CS_CONNECTED)
		{

		}
	}


	void MacClientTCPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool MacClientTCPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool MacClientTCPNetwork::Init()
	{
		return false;
	}*/

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	/*MacClientUDPNetwork::MacClientUDPNetwork()
	{

	}

	MacClientUDPNetwork::~MacClientUDPNetwork()
	{

	}

	bool MacClientUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("Mac:UDP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("Mac:UDP: Connected");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void MacClientUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("Mac:UDP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("Mac:UDP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void MacClientUDPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool MacClientUDPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool MacClientUDPNetwork::Init()
	{
		return false;
	}*/

}