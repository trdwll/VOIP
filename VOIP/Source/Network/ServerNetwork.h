#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	/** Use TCP for text */
	class ServerTCPNetwork : TCPNetwork
	{
	public:
		ServerTCPNetwork();
		virtual ~ServerTCPNetwork();

		virtual void SendChatMessage(char* Message) = 0;

		// TODO: Another implementation that can disconnect us from a current server before connecting to another
		virtual void Connect() = 0;

		// TODO: Another implementation that takes in an ip:port as the identifier for the server and disconnects specifically from it if we're connected
		virtual void Disconnect() = 0;

	};

	/** Use UDP for voice */
	class ServerUDPNetwork : UDPNetwork
	{
	public:
		ServerUDPNetwork();
		virtual ~ServerUDPNetwork();

		// TODO: Another implementation that can disconnect us from a current server before connecting to another
		virtual void Connect() = 0;

		// TODO: Another implementation that takes in an ip:port as the identifier for the server and disconnects specifically from it if we're connected
		virtual void Disconnect() = 0;

	};
}

