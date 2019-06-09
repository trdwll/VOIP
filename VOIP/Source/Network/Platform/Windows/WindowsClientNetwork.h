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

		bool Connect() override;
		void Disconnect() override;

		void SendChatMessage(const std::string& Message) override;

		void Test() {}

	private:
		/** Variables */

		SOCKET m_Socket;
		sockaddr_in m_Hints;
		bool m_bIsReceiveThreadRunning;
		std::thread m_ReceiveThread;

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
		void ListenReceiveThread(MessageReceivedHandler handler) override;

		/** Receive the content from the thread */
		bool Receive(MessageReceivedHandler handler) override;

	};

	/** Use UDP for voice */
	class WindowsClientUDPNetwork : public ClientUDPNetwork
	{
	public:

		WindowsClientUDPNetwork();
		virtual ~WindowsClientUDPNetwork();

		bool Connect() override;
		void Disconnect() override;

		/** Create the receive thread */
		void ListenReceiveThread(MessageReceivedHandler handler) override;

		/** Receive the content from the thread */
		bool Receive(MessageReceivedHandler handler) override;

	private:
		bool Init() override;
	};
}