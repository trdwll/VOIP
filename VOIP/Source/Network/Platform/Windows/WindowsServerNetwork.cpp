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

		Disconnect();

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


	/*void WindowsServerTCPNetwork::SendChatMessage(const std::string& Message)
	{
		if (!Message.empty())
		{
			for (int32 i = 0; i < master.fd_count; i++)
			{
				SOCKET client = master.fd_array[i];
				if ((client != m_ListenSocket) && (client != NULL))
				{
					send(client, Message.c_str(), Message.size() + 1, 0);
				}
			}
		}
	}*/

	void WindowsServerTCPNetwork::SendChatMessage(const std::string& Message, SOCKET ClientSocket)
	{
		if (!Message.empty())
		{
			send(ClientSocket, Message.c_str(), Message.size() + 1, 0);
		}
	}

	void WindowsServerTCPNetwork::ListenReceiveThread(MessageReceivedHandler handler)
	{

	}

	bool WindowsServerTCPNetwork::Receive(MessageReceivedHandler handler)
	{
		return false;
	}

	bool WindowsServerTCPNetwork::Init()
	{
		WSADATA wsaData;

		int32 Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (Result != 0)
		{
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

		int32 Result = bind(serverSocket, (sockaddr*)&m_Hints, sizeof(m_Hints));
		if (Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to bind address/port ({0}:{1}). Error: {3}", m_host, m_port, WSAGetLastError());
			WSACleanup();
			return SOCKET_ERROR;
		}

		int32 Result2 = listen(serverSocket, SOMAXCONN);
		if (Result2 == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to listen on address/port ({0}:{1}). Error: {3}", m_host, m_port, WSAGetLastError());
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
			VOIP_CORE_ERROR("Socket is invalid.");
			return;
		}

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

					FD_SET(client, &master);

					std::string msg = "Welcome to the server";
					send(client, msg.c_str(), msg.size() + 1, 0);
				}
				else
				{
					char buf[DEFAULT_BUFFER_SIZE];
					ZeroMemory(buf, DEFAULT_BUFFER_SIZE);

					int32 ReceivedBytes = recv(socket, buf, DEFAULT_BUFFER_SIZE, 0);
					if (ReceivedBytes <= 0)
					{
						closesocket(socket);
						FD_CLR(socket, &master);
					}
					else
					{
						if (m_MessageReceivedEvent != NULL)
						{
							m_MessageReceivedServerEvent(this, socket, std::string(buf, 0, ReceivedBytes));
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

	void WindowsServerUDPNetwork::ListenReceiveThread(MessageReceivedHandler handler)
	{

	}

	bool WindowsServerUDPNetwork::Receive(MessageReceivedHandler handler)
	{
		return false;
	}

	bool WindowsServerUDPNetwork::Init()
	{
		return false;
	}

}