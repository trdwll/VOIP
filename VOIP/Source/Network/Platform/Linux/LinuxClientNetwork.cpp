#include "voippch.h"
#include "Network/Platform/Linux/LinuxClientNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	/*LinuxClientTCPNetwork::LinuxClientTCPNetwork()
	{

	}

	LinuxClientTCPNetwork::~LinuxClientTCPNetwork()
	{

	}

	bool LinuxClientTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("LINUX:TCP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		if (m_host.empty() || m_port == 0)
		{
			VOIP_CORE_ERROR("Host or port haven't been set.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return false;
		}

		VOIP_CLIENT_INFO("LINUX:TCP: Connected to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
		return true;
	}

	void LinuxClientTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("LINUX:TCP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("LINUX:TCP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void LinuxClientTCPNetwork::SendChatMessage(const std::string& Message)
	{
		if (m_ConnectionStatus == EConnectionStatus::CS_CONNECTED)
		{

		}
	}


	void LinuxClientTCPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool LinuxClientTCPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool LinuxClientTCPNetwork::Init()
	{
		return false;
	}*/

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	/*LinuxClientUDPNetwork::LinuxClientUDPNetwork()
	{

	}

	LinuxClientUDPNetwork::~LinuxClientUDPNetwork()
	{

	}

	bool LinuxClientUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("LINUX:UDP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("LINUX:UDP: Connected");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void LinuxClientUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("LINUX:UDP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("LINUX:UDP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void LinuxClientUDPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{

	}

	bool LinuxClientUDPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		return false;
	}

	bool LinuxClientUDPNetwork::Init()
	{
		return false;
	}*/

}