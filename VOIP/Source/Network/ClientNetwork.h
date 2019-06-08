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
	class ClientTCPNetwork : public TCPNetwork
	{
	public:

		ClientTCPNetwork();
		virtual ~ClientTCPNetwork();

		void Connect() override;
		void Disconnect() override;

		void SendChatMessage(char* Message) override;

	private:

#if VOIP_PLATFORM_WINDOWS

		WSADATA m_wsaData;
		SOCKET m_ConnectSocket = INVALID_SOCKET;
		struct addrinfo* m_result = NULL;
		struct addrinfo* m_ptr = NULL;
		struct addrinfo m_hints;
		
		char m_recvBuffer[512];

		int32 m_Result;
		int32 m_recvBufferLength = 512;

#endif

	};

	/** Use UDP for voice */
	class ClientUDPNetwork : public UDPNetwork
	{
	public:

		ClientUDPNetwork();
		virtual ~ClientUDPNetwork();

		void Connect() override;
		void Disconnect() override;
	};
}