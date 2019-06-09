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
		void SendChatMessage(const std::string& Message) override;

	private:
		bool Init() override;

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