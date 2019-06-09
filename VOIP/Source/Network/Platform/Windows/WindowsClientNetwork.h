#pragma once
#include "Network/ClientNetwork.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

namespace VOIP {

	/** Use TCP for text */
	class WindowsClientTCPNetwork : public ClientTCPNetwork
	{
	public:

		WindowsClientTCPNetwork();
		virtual ~WindowsClientTCPNetwork();

		void Connect() override;
		void Disconnect() override;

		void SendChatMessage(char* Message) override;

	private:

		WSADATA m_wsaData;
		SOCKET m_ConnectSocket = INVALID_SOCKET;
		struct addrinfo* m_result = NULL;
		struct addrinfo* m_ptr = NULL;
		struct addrinfo m_hints;
		
		char m_recvBuffer[512];

		int32 m_Result;
		int32 m_recvBufferLength = 512;
	};

	/** Use UDP for voice */
	class WindowsClientUDPNetwork : public ClientUDPNetwork
	{
	public:

		WindowsClientUDPNetwork();
		virtual ~WindowsClientUDPNetwork();

		void Connect() override;
		void Disconnect() override;
	};
}