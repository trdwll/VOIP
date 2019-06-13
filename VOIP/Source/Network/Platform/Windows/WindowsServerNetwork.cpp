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
		Disconnect(); // Probably isn't smart doing this here, but it should be ok
	}

	bool WindowsServerTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("TCP: Binding to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		if (!Init())
		{
			VOIP_CORE_ERROR("Init failed!");
			return false;
		}

		RunThread();

		return true;
	}

	void WindowsServerTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("TCP: Unbinding from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		std::string msg = "Server is shutting down.";

		FD_CLR(m_ListenSocket, &master);
		closesocket(m_ListenSocket);

		// A for loop could work better here since we're iterating over all clients
		while (master.fd_count > 0)
		{
			SOCKET client = master.fd_array[0];

			send(client, msg.c_str(), msg.size() + 1, 0);

			FD_CLR(client, &master);

			closesocket(client);
		}
		
		WSACleanup();

		if (m_bIsRunThreadRunning)
		{
			m_bIsRunThreadRunning = false;
			m_RunThread.join();
		}

		VOIP_CLIENT_INFO("TCP: Unbinded");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}


	void WindowsServerTCPNetwork::SendChatMessageToAll(std::string Message)
	{
		if (!Message.empty())
		{
			for (uint32 i = 0; i < master.fd_count; i++)
			{
				SOCKET client = master.fd_array[i];
				if ((client != m_ListenSocket))// && (client != NULL))
				{
					send(client, Message.c_str(), Message.size() + 1, 0);
				}
			}
		}
	}

	void WindowsServerTCPNetwork::SendChatMessageTo(std::string Message, SOCKET ClientSocket)
	{
		if (!Message.empty())
		{
			send(ClientSocket, Message.c_str(), Message.size() + 1, 0);
		}
	}

	void WindowsServerTCPNetwork::SetCallback(ServerMessageReceivedHandler handler)
	{
		m_ServerMessageReceivedEvent = handler;
	}

	bool WindowsServerTCPNetwork::Init()
	{
		WSADATA wsaData;

		int32 Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (Result != 0)
		{
			VOIP_CORE_ERROR("WSAStartup failed. Error: {0}", WSAGetLastError());
			return false;
		}

		return Result == 0;
	}

	SOCKET WindowsServerTCPNetwork::CreateSocket()
	{
		SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (serverSocket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("Socket can't be created. Error: {0}", WSAGetLastError());
			WSACleanup();
			return INVALID_SOCKET;
		}

		m_Hints.sin_family = AF_INET;
		m_Hints.sin_port = m_port;
		inet_pton(AF_INET, m_host.c_str(), &m_Hints.sin_addr);

		// Bind the socket to the address
		int32 Result = bind(serverSocket, (sockaddr*)& m_Hints, sizeof(m_Hints));
		if (Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to bind address/port ({0}:{1}). Error: {2}", m_host, m_port, WSAGetLastError());
			WSACleanup();
			return SOCKET_ERROR;
		}

		// Start listening with the socket
		int32 Result2 = listen(serverSocket, SOMAXCONN);
		if (Result2 == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to listen on address/port ({0}:{1}). Error: {2}", m_host, m_port, WSAGetLastError());
			WSACleanup();
			return SOCKET_ERROR;
		}

		return serverSocket;
	}

	void WindowsServerTCPNetwork::RunThread()
	{
		this->m_RunThread = std::thread([&]()
		{
			Run();
		});
	}

	void WindowsServerTCPNetwork::Run()
	{
		m_ListenSocket = CreateSocket();

		if (m_ListenSocket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("Socket is invalid. Error: {0}", WSAGetLastError());
			return;
		}

		// fd_set master;
		FD_ZERO(&master);
		FD_SET(m_ListenSocket, &master);

		m_bIsRunThreadRunning = true;

		std::cout << "Server is starting up." << std::endl;

		while (m_bIsRunThreadRunning)
		{
			fd_set copy = master;
			
			int32 SocketCount = select(0, &copy, nullptr, nullptr, nullptr);
			for (int32 i = 0; i < SocketCount; i++)
			{
				SOCKET socket = copy.fd_array[i];

				if (socket == m_ListenSocket)
				{
					// TODO: set ipaddr
					SOCKET client = accept(m_ListenSocket, nullptr, nullptr);

					VOIP_CORE_INFO("'USERNAME<IPADDR>' connected");

					FD_SET(client, &master);

					std::string msg = "Welcome to the server";
					send(client, msg.c_str(), msg.size() + 1, 0);
				}
				else
				{
					char buf[DEFAULT_BUFFER_SIZE];
					ZeroMemory(buf, DEFAULT_BUFFER_SIZE);

					uint32 ReceivedBytes = recv(socket, buf, DEFAULT_BUFFER_SIZE, 0);
					if (ReceivedBytes == 0) // <= 0 and should be int32?
					{
						closesocket(socket);
						FD_CLR(socket, &master);
					}
					else
					{
						std::string msg = std::string(buf, 0, ReceivedBytes);
						if (m_ServerMessageReceivedEvent != NULL && !msg.empty())
						{
							// SendChatMessageToAll(msg);
							m_ServerMessageReceivedEvent(this, socket, msg);
							VOIP_CORE_INFO("Message received: {0}", msg);
						}
					}
				}
			}
		}

		Disconnect();
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