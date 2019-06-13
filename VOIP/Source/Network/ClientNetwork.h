#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	typedef void(*ClientMessageReceivedHandler)(std::string message);

	/** Use TCP for text */
	class ClientTCPNetwork : public TCPNetwork
	{
	public:
		ClientTCPNetwork();
		virtual ~ClientTCPNetwork();

		/** Create the receive thread */
		virtual void ListenReceiveThread(ClientMessageReceivedHandler handler) = 0;

		/** Receive the content from the thread */
		virtual bool Receive(ClientMessageReceivedHandler handler) = 0;

		virtual void SendChatMessage(std::string Message) = 0;

	protected:
		ClientMessageReceivedHandler m_ClientMessageReceivedEvent;
	};

	/** Use UDP for voice */
	class ClientUDPNetwork : public UDPNetwork
	{
	public:
		ClientUDPNetwork();
		virtual ~ClientUDPNetwork();
	};
}

