#include "voippch.h"
#include "Network/ServerNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	ServerTCPNetwork::ServerTCPNetwork()
	{

	}

	ServerTCPNetwork::~ServerTCPNetwork()
	{

	}

	void ServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

#if VOIP_PLATFORM_WINDOWS

		m_Result = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
		if (m_Result != 0)
		{
			VOIP_CORE_ERROR("Unable to initialize WSAStartup. Error: {0}", m_Result);
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return;
		}

		ZeroMemory(&m_hints, sizeof(m_hints));
		m_hints.ai_family = AF_INET;
		m_hints.ai_socktype = SOCK_STREAM;
		m_hints.ai_protocol = IPPROTO_TCP;
		m_hints.ai_flags = AI_PASSIVE;

		// We can do to_string().c_str() or do a cast to uint16 lol
		m_Result = getaddrinfo(NULL, std::to_string(m_port).c_str(), &m_hints, &m_result);
		if (m_Result != 0)
		{
			VOIP_CORE_ERROR("Unable to getaddrinfo. Error: {0}", m_Result);
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			WSACleanup();
			return;
		}
		
		m_ListenSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
		if (m_ListenSocket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("Unable to create socket. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			freeaddrinfo(m_result);
			WSACleanup();
			return;
		}
		
		// TODO: replace with our IP that we've specified
		m_Result = bind(m_ListenSocket, m_result->ai_addr, (uint32)m_result->ai_addrlen);
		if (m_Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to bind socket. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			freeaddrinfo(m_result);
			closesocket(m_ListenSocket);
			WSACleanup();
			return;
		}

		freeaddrinfo(m_result);

		m_Result = listen(m_ListenSocket, SOMAXCONN);
		if (m_Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to listen on socket. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			closesocket(m_ListenSocket);
			WSACleanup();
			return;
		}
		
		if (m_Result == 0)
		{
			VOIP_CLIENT_INFO("Listening for client connection...");
		}

		m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
		if (m_ClientSocket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("Unable to accept socket. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			closesocket(m_ListenSocket);
			WSACleanup();
			return;
		}

		closesocket(m_ListenSocket);

		do {
			VOIP_CORE_INFO("m_Result == {0}", m_Result);
			m_Result = recv(m_ClientSocket, m_recvBuffer, m_recvBufferLength, 0);
			if (m_Result > 0)
			{
				VOIP_CORE_INFO("Bytes received: {0}", m_Result);

				m_SendResult = send(m_ClientSocket, m_recvBuffer, m_recvBufferLength, 0);
				if (m_SendResult == SOCKET_ERROR)
				{
					VOIP_CORE_ERROR("Unable to send to ClientSocket. Error: {0}", WSAGetLastError());
					m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
					closesocket(m_ClientSocket);
					WSACleanup();
					return;
				}

				m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
				VOIP_CORE_INFO("Bytes sent: {0}", m_SendResult);
			}
			else if (m_Result == 0)
			{
				VOIP_CORE_INFO("Connection closing");
			}
			else
			{
				VOIP_CORE_ERROR("recv failed. Error: {0}", WSAGetLastError());
				m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
				closesocket(m_ClientSocket);
				WSACleanup();
				return;
			}
		} while (m_Result > 0);

		Disconnect();
#endif
	}

	void ServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

#if VOIP_PLATFORM_WINDOWS

		m_Result = shutdown(m_ClientSocket, SD_SEND);
		if (m_Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Shutdown failed. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTERROR;
			closesocket(m_ClientSocket);
			WSACleanup();
			return;
		}

		closesocket(m_ClientSocket);
		WSACleanup();

#endif

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void ServerTCPNetwork::SendChatMessage(char* Message)
	{

	}

	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	ServerUDPNetwork::ServerUDPNetwork()
	{

	}

	ServerUDPNetwork::~ServerUDPNetwork()
	{

	}

	void ServerUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void ServerUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

}