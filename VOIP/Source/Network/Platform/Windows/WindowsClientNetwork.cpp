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
		Disconnect(); // This probably isn't safe, but #yolo for now
	}

	bool WindowsClientTCPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("WINDOWS:TCP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		if (m_host.empty() || m_port == 0)
		{
			VOIP_CORE_ERROR("Host or port haven't been set.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return false;
		}

		if (!Init()) return false;

		// Create the socket for the client
		m_Socket = CreateSocket();
		if (m_Socket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("The socket was unable to be created.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return false;
		}

		// Connect to the host
		int32 Result = connect(m_Socket, (sockaddr*)&m_Hints, sizeof(m_Hints));
		if (Result == SOCKET_ERROR)
		{
			VOIP_CORE_ERROR("Unable to connect to the host.");
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return false;
		}


		VOIP_CLIENT_INFO("WINDOWS:TCP: Connected to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;
		return true;
	}

	void WindowsClientTCPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("WINDOWS:TCP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		closesocket(m_Socket);
		WSACleanup();

		if (m_bIsReceiveThreadRunning)
		{
			m_bIsReceiveThreadRunning = false;
			m_ReceiveThread.join();
		}

		VOIP_CLIENT_INFO("WINDOWS:TCP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	bool WindowsClientTCPNetwork::Init()
	{
		WSADATA wsaData;
		
		uint32 Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (Result != 0)
		{
			VOIP_CORE_ERROR("WSAStartup failed. Error: {0}", Result);
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			return false;
		}

		return Result == 0;
	}

	SOCKET WindowsClientTCPNetwork::CreateSocket()
	{
		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket == INVALID_SOCKET)
		{
			VOIP_CORE_ERROR("CreateSocket() failed. Error: {0}", WSAGetLastError());
			m_ConnectionStatus = EConnectionStatus::CS_CONNECTERROR;
			WSACleanup();
			return INVALID_SOCKET;
		}

		m_Hints.sin_family = AF_INET;
		m_Hints.sin_port = m_port;
		inet_pton(AF_INET, m_host.c_str(), &m_Hints.sin_addr);

		return clientSocket;
	}

	void WindowsClientTCPNetwork::ReceiveThread()
	{
		m_bIsReceiveThreadRunning = true;
		while (m_bIsReceiveThreadRunning)
		{
			char buf[DEFAULT_BUFFER_SIZE];
			ZeroMemory(buf, DEFAULT_BUFFER_SIZE);

			uint32 BytesReceived = recv(m_Socket, buf, DEFAULT_BUFFER_SIZE, 0);
			if (BytesReceived > 0)
			{
				if (m_ClientMessageReceivedEvent != NULL)
				{
					m_ClientMessageReceivedEvent(std::string(buf, 0, BytesReceived));
				}
			}
		}
	}

	void WindowsClientTCPNetwork::ListenReceiveThread(ClientMessageReceivedHandler handler)
	{
		m_ClientMessageReceivedEvent = handler;

		this->m_ReceiveThread = std::thread([&]() 
		{
			ReceiveThread();
		});
	}

	bool WindowsClientTCPNetwork::Receive(ClientMessageReceivedHandler handler)
	{
		m_ClientMessageReceivedEvent = handler;

		if (m_Socket == INVALID_SOCKET)
		{
			return false;
		}

		char buf[DEFAULT_BUFFER_SIZE];

		int32 BytesReceived = recv(m_Socket, buf, DEFAULT_BUFFER_SIZE, 0);
		if (BytesReceived > 0)
		{
			if (m_ClientMessageReceivedEvent != NULL)
			{
				m_ClientMessageReceivedEvent(std::string(buf, 0, BytesReceived));
			}
		}

		return true;
	}

	void WindowsClientTCPNetwork::SendChatMessage(std::string Message)
	{
		if (m_ConnectionStatus == EConnectionStatus::CS_CONNECTED)
		{
			if (m_Socket == INVALID_SOCKET)
			{
				if (!Message.empty())
				{
					send(m_Socket, Message.c_str(), Message.size() + 1, 0);
				}
				else
				{
					VOIP_CORE_WARN("Message is empty");
				}
			}
			else
			{
				VOIP_CORE_ERROR("Socket is invalid");
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

	bool WindowsClientUDPNetwork::Connect()
	{
		VOIP_CLIENT_INFO("WINDOWS:UDP: Connecting to {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTING;

		VOIP_CLIENT_INFO("WINDOWS:UDP: Connected");
		m_ConnectionStatus = EConnectionStatus::CS_CONNECTED;

		return true;
	}

	void WindowsClientUDPNetwork::Disconnect()
	{
		VOIP_CLIENT_INFO("WINDOWS:UDP: Disconnecting from {0}:{1}", m_host, m_port);
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTING;

		VOIP_CLIENT_INFO("WINDOWS:UDP: Disconnected");
		m_ConnectionStatus = EConnectionStatus::CS_DISCONNECTED;
	}

	bool WindowsClientUDPNetwork::Init()
	{
		return false;
	}

}