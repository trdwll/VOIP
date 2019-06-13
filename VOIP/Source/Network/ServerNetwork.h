#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	class ServerTCPNetwork;

#ifdef VOIP_PLATFORM_WINDOWS
	// typedef std::function<void (ServerTCPNetwork* Listener, SOCKET socketID, std::string message)> *ServerMessageReceivedHandler;
	typedef void(*ServerMessageReceivedHandler)(class ServerTCPNetwork* Listener, SOCKET socketID, std::string message);
#elif defined(VOIP_PLATFORM_LINUX) || defined(VOIP_PLATFORM_MAC)
	typedef void(*ServerMessageReceivedHandler)(class ServerTCPNetwork* Listener, int32 socketID, std::string message);
#endif

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

		/** Set the callback method for messages. */
		virtual void SetCallback(ServerMessageReceivedHandler handler) = 0;

	protected:
		ServerMessageReceivedHandler m_ServerMessageReceivedEvent;
	};

	/** Use UDP for voice */
	class ServerUDPNetwork : public UDPNetwork
	{
	public:
		ServerUDPNetwork();
		virtual ~ServerUDPNetwork();
	};
}

