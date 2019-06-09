#include "voippch.h"
#include "Network/Platform/Windows/WindowsClientNetwork.h"


namespace VOIP {

	/************************************************************************/
	/* TCP Networking                                                       */
	/************************************************************************/

	WindowsClientTCPNetwork::WindowsClientTCPNetwork()
	{

	}

	WindowsClientTCPNetwork::~WindowsClientTCPNetwork()
	{

	}

	void WindowsClientTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("WINDOWS:TCP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		if (m_host.empty() || m_port == 0)
		{
			VOIP_CORE_ERROR("Host or port haven't been set.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return;
		}

		m_Result = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
		if (m_Result != 0)
		{
			VOIP_CORE_ERROR("WSAStartup failed. Error: {0}", m_Result);
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return;
		}

		ZeroMemory(&m_hints, sizeof(m_hints));
		m_hints.ai_family = AF_UNSPEC;
		m_hints.ai_socktype = SOCK_STREAM;
		m_hints.ai_protocol = IPPROTO_TCP;

		m_Result = getaddrinfo(m_host.c_str(), std::to_string(m_port).c_str(), &m_hints, &m_result);
		if (m_Result != 0)
		{
			VOIP_CORE_ERROR("getaddrinfo failed. Error: {0}", m_Result);
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			WSACleanup();
			return;
		}

		for (m_ptr = m_result; m_ptr != NULL; m_ptr = m_ptr->ai_next)
		{
			m_ConnectSocket = socket(m_ptr->ai_family, m_ptr->ai_socktype, m_ptr->ai_protocol);
			if (m_ConnectSocket == INVALID_SOCKET)
			{
				VOIP_CORE_ERROR("socket failed. Error: {0}", WSAGetLastError());
				m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
				WSACleanup();
				return;
			}

			m_Result = connect(m_ConnectSocket, m_ptr->ai_addr, (int32)m_ptr->ai_addrlen);
			if (m_Result == SOCKET_ERROR)
			{
				closesocket(m_ConnectSocket);
				m_ConnectSocket = INVALID_SOCKET;
				continue;
			}

			VOIP_CORE_INFO("Connected to the server");
			break;
		}

		freeaddrinfo(m_result);

		if (m_ConnectSocket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("Unable to connect to the server.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			WSACleanup();
			return;
		}

		char buf[4096];
		std::string userInput;

		while (true)
		{
			std::cout << "USERNAME:" << "> ";
			getline(std::cin, userInput);

			int sendResult = send(m_ConnectSocket, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{
				// Wait for response
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(m_ConnectSocket, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
				}
			}
		}
		
		/*do {
			m_Result = recv(m_ConnectSocket, m_recvBuffer, m_recvBufferLength, 0);
			if (m_Result > 0)
			{
				VOIP_CLIENT_INFO("TCP: Connected");
				m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

				VOIP_CORE_INFO("Bytes Received: {0}", m_Result);
			}
			else if (m_result == 0)
			{
				VOIP_CORE_INFO("Connection Closed");
			}
			else
			{
				VOIP_CORE_ERROR("recv failed. Error: {0}", WSAGetLastError());
				m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			}

		} while (m_Result > 0);*/


		Disconnect();
	}

	void WindowsClientTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("WINDOWS:TCP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		m_Result = shutdown(m_ConnectSocket, SD_SEND);
		if (m_Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Shutdown failed. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTERROR;
			closesocket(m_ConnectSocket);
			WSACleanup();
			return;
		}

		closesocket(m_ConnectSocket);
		WSACleanup();

		VOIP_CLIENT_INFO("WINDOWS:TCP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	void WindowsClientTCPNetwork::SendChatMessage(char* Message)
	{
		//if (m_ConnectionStatus == EConnectionStatus::CS_CONNECTED)
		{
			if (m_ConnectSocket != INVALID_SOCKET)
			{
				m_Result = send(m_ConnectSocket, Message, (int32)strlen(Message), 0);
				if (m_Result == SOCKET_ERROR)
				{
					VOIP_CORE_ERROR("Unable to send a message. Error: {0}", WSAGetLastError());
					m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
					WSACleanup();
					return;
				}

				VOIP_CORE_INFO("Bytes sent: {0}", m_Result);
			}
		}
	}


	/************************************************************************/
	/* UDP Networking                                                       */
	/************************************************************************/

	WindowsClientUDPNetwork::WindowsClientUDPNetwork()
	{

	}

	WindowsClientUDPNetwork::~WindowsClientUDPNetwork()
	{

	}

	void WindowsClientUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("WINDOWS:UDP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("WINDOWS:UDP: Connected");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void WindowsClientUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("WINDOWS:UDP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("WINDOWS:UDP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

}