#pragma once
#include "Network/ServerNetwork.h"

namespace VOIP {

	/** Use TCP for text */
	class MacServerTCPNetwork : public ServerTCPNetwork
	{
	//public:

	//	MacServerTCPNetwork();
	//	virtual ~MacServerTCPNetwork();

	//	bool Connect() override;
	//	void Disconnect() override;
	//	void SendChatMessage(const std::string& Message) override;

	//	/** Create the receive thread */
	//	void ListenReceiveThread(ClientMessageReceivedHandler handler) override;

	//	/** Receive the content from the thread */
	//	bool Receive(ClientMessageReceivedHandler handler) override;

	//private:
	//	bool Init() override;
	};

	/** Use UDP for voice */
	class MacServerUDPNetwork : public ServerUDPNetwork
	{
	//public:

	//	MacServerUDPNetwork();
	//	virtual ~MacServerUDPNetwork();

	//	bool Connect() override;
	//	void Disconnect() override;

	//	/** Create the receive thread */
	//	void ListenReceiveThread(ClientMessageReceivedHandler handler) override;

	//	/** Receive the content from the thread */
	//	bool Receive(ClientMessageReceivedHandler handler) override;

	//private:
	//	bool Init() override;
	};
}