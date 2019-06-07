#include "voippch.h"
#include "Network/ClientNetwork.h"


#if VOIP_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#endif

namespace VOIP {


	ClientTCPNetwork::ClientTCPNetwork()
	{

	}

	ClientTCPNetwork::~ClientTCPNetwork()
	{

	}

	void ClientTCPNetwork::Connect()
	{
		TCPNetwork::Connect();

		VOIP_CLIENT_INFO("Connecting to {0}:{1}", GetHost(), GetPort());

		bConnected = true;

		VOIP_CLIENT_INFO("Connected");
	}

	void ClientTCPNetwork::Disconnect()
	{
		TCPNetwork::Disconnect();

		VOIP_CLIENT_INFO("Disconnecting from {0}:{1}", GetHost(), GetPort());

		bConnected = false;

		VOIP_CLIENT_INFO("Disconnected");
	}

}