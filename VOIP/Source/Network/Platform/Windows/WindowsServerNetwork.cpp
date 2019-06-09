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

	void WindowsServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

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

		fd_set master;
		FD_ZERO(&master);
		FD_SET(m_ListenSocket, &master);
		
		if (m_Result == 0)
		{
			VOIP_CLIENT_INFO("Listening for client connection...");
			
			while (true)
			{
				fd_set copy = master;

				// See who's talking to us
				int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
				for (int i = 0; i < socketCount; i++)
				{
					// Makes things easy for us doing this assignment
					SOCKET sock = copy.fd_array[i];

					// Is it an inbound communication?
					if (sock == m_ListenSocket)
					{
						// Accept a new connection
						SOCKET client = accept(m_ListenSocket, nullptr, nullptr);

						// Add the new connection to the list of connected clients
						FD_SET(client, &master);

						// Send a welcome message to the connected client
						std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
						send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
					}
					else
					{
						char buf[4096];
						ZeroMemory(buf, 4096);

						// Receive message
						int bytesIn = recv(sock, buf, 4096, 0);
						if (bytesIn <= 0)
						{
							// Drop the client
							closesocket(sock);
							FD_CLR(sock, &master);
						}
						else
						{
							for (int i = 0; i < master.fd_count; i++)
							{
								SOCKET outSock = master.fd_array[i];
								if (outSock != m_ListenSocket && outSock != sock)
								{
									std::ostringstream ss;
									ss << "SOCKET #" << sock << ": " << buf << "\r\n";
									std::string strOut = ss.str();

									send(outSock, strOut.c_str(), strOut.size() + 1, 0);
								}
							}
						}
					}
				}


				/*m_ClientSocket = accept(m_ListenSocket, NULL, NULL);
				if (m_ClientSocket == INVALID_SOCKET)
				{
					VOIP_CORE_ERROR("Unable to accept socket. Error: {0}", WSAGetLastError());
					m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
					closesocket(m_ListenSocket);
					WSACleanup();
					return;
				}*/
			}
		}

		/*do {
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
		} while (m_Result > 0);*/

		Disconnect();
	}

	void WindowsServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		m_Result = shutdown(m_ClientSocket, SD_SEND);
		if (m_Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Shutdown failed. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTERROR;
			closesocket(m_ClientSocket);
			WSACleanup();
			return;
		}

		closesocket(m_ListenSocket);
		closesocket(m_ClientSocket);
		WSACleanup();

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void WindowsServerTCPNetwork::SendChatMessage(char* Message)
	{

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

	void WindowsServerUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("UDP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("UDP: Binded");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
	}

	void WindowsServerUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("UDP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("UDP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

}