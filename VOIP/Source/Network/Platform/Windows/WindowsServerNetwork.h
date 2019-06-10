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

		bool Connect() override;
		void Disconnect() override;

		// sends to all users except self
		void SendChatMessageToAll(std::string Message) override;

		// send to a specific user
		void SendChatMessageTo(std::string Message, SOCKET ClientSocket) override;

		void SetCallback(ServerMessageReceivedHandler handler) override;

	private:
		/** Variables */

		sockaddr_in m_Hints;
		bool m_bIsRunThreadRunning;
		std::thread m_RunThread;
		SOCKET m_ListenSocket;

		fd_set master;

	private:
		/** Methods */

		/** Initialize WSA */
		bool Init() override;

		/** Create the socket for the client to send and receive. */
		SOCKET CreateSocket();

		void RunThread();

		void Run();
	};

	/** Use UDP for voice */
	class WindowsServerUDPNetwork : public ServerUDPNetwork
	{
	public:

		WindowsServerUDPNetwork();
		virtual ~WindowsServerUDPNetwork();

		bool Connect() override;
		void Disconnect() override;

	private:
		bool Init() override;
	};
}