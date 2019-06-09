#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	/** Use TCP for text */
	class ServerTCPNetwork : public TCPNetwork
	{
	public:
		ServerTCPNetwork();
		virtual ~ServerTCPNetwork();

		// sends to all users except self
		virtual void SendChatMessageToAll(std::string Message) = 0; 
		
		// send to a specific user
		virtual void SendChatMessageTo(std::string Message, SOCKET ClientSocket) = 0; 
	};

	/** Use UDP for voice */
	class ServerUDPNetwork : public UDPNetwork
	{
	public:
		ServerUDPNetwork();
		virtual ~ServerUDPNetwork();
	};
}

