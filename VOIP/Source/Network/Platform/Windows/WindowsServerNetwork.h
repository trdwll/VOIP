#pragma once
#include "Network/ServerNetwork.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

namespace VOIP {

	/** Use TCP for text */
	class WindowsServerTCPNetwork : public ServerTCPNetwork
	{
	public:

		WindowsServerTCPNetwork();
		virtual ~WindowsServerTCPNetwork();

		void Connect() override;
		void Disconnect() override;
		void SendChatMessage(char* Message) override;

		WSADATA m_wsaData;
		int32 m_Result;

		SOCKET m_ListenSocket = INVALID_SOCKET;
		SOCKET m_ClientSocket = INVALID_SOCKET;

		struct addrinfo* m_result = NULL;
		struct addrinfo m_hints;

		int32 m_SendResult;
		char m_recvBuffer[512];
		int32 m_recvBufferLength = 512;

	};

	/** Use UDP for voice */
	class WindowsServerUDPNetwork : public ServerUDPNetwork
	{
	public:

		WindowsServerUDPNetwork();
		virtual ~WindowsServerUDPNetwork();

		void Connect() override;
		void Disconnect() override;

	};
}