#pragma once
#include "Network/Network.h"

#if VOIP_PLATFORM_WINDOWS
// TODO: Move this stuff into the source file if we can (forward decl)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#endif

namespace VOIP {

	/** Use TCP for text */
	class ServerTCPNetwork : public TCPNetwork
	{
	public:

		ServerTCPNetwork();
		virtual ~ServerTCPNetwork();

		void Connect() override;
		void Disconnect() override;
		void SendChatMessage(char* Message) override;

#if VOIP_PLATFORM_WINDOWS

		WSADATA m_wsaData;
		int32 m_Result;

		SOCKET m_ListenSocket = INVALID_SOCKET;
		SOCKET m_ClientSocket = INVALID_SOCKET;

		struct addrinfo* m_result = NULL;
		struct addrinfo m_hints;

		int32 m_SendResult;
		char m_recvBuffer[512];
		int32 m_recvBufferLength = 512;

#endif

	};

	/** Use UDP for voice */
	class ServerUDPNetwork : public UDPNetwork
	{
	public:

		ServerUDPNetwork();
		virtual ~ServerUDPNetwork();

		void Connect() override;
		void Disconnect() override;

#if VOIP_PLATFORM_WINDOWS

#endif
	};
}