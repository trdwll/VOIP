#pragma once
#include "Network/ClientNetwork.h"

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

namespace VOIP {

	typedef void(*MessageReceivedHandler)(std::string message);

	/** Use TCP for text */
	class WindowsClientTCPNetwork : public ClientTCPNetwork
	{
	public:

		WindowsClientTCPNetwork();
		virtual ~WindowsClientTCPNetwork();

		bool Connect() override;
		void Disconnect() override;

		void SendChatMessage(const std::string& Message) override;

	private:
		/** Variables */

		SOCKET m_Socket;
		sockaddr_in m_Hints;
		bool m_bIsReceiveThreadRunning;
		std::thread m_ReceiveThread;

		MessageReceivedHandler MessageReceivedEvent;

	private:
		/** Methods */

		/** Initialize WSAStartup */
		bool Init() override;

		/** Create the socket for the client to send and receive. */
		SOCKET CreateSocket();

		/** The method for m_ReceiveThread */
		void ReceiveThread();

	public:
		/** Create the receive thread */
		void ListenReceiveThread(MessageReceivedHandler handler);

		/** Receive the content from the thread */
		bool Receive(MessageReceivedHandler handler);

	};

	/** Use UDP for voice */
	class WindowsClientUDPNetwork : public ClientUDPNetwork
	{
	public:

		WindowsClientUDPNetwork();
		virtual ~WindowsClientUDPNetwork();

		bool Connect() override;
		void Disconnect() override;

	private:
		bool Init() override;
	};
}