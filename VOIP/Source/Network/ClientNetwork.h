#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	/** Use TCP for text */
	class ClientTCPNetwork : TCPNetwork
	{
	public:
		ClientTCPNetwork();
		virtual ~ClientTCPNetwork();

		virtual void SendChatMessage(char* Message) = 0;

		// TODO: Another implementation that can disconnect us from a current Client before connecting to another
		virtual void Connect() = 0;

		// TODO: Another implementation that takes in an ip:port as the identifier for the Client and disconnects specifically from it if we're connected
		virtual void Disconnect() = 0;
	};

	/** Use UDP for voice */
	class ClientUDPNetwork : UDPNetwork
	{
	public:
		ClientUDPNetwork();
		virtual ~ClientUDPNetwork();

		// TODO: Another implementation that can disconnect us from a current Client before connecting to another
		virtual void Connect() = 0;

		// TODO: Another implementation that takes in an ip:port as the identifier for the Client and disconnects specifically from it if we're connected
		virtual void Disconnect() = 0;
	};
}

