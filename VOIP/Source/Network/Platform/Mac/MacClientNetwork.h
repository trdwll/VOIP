#pragma once
#include "Network/ClientNetwork.h"

namespace VOIP {

	/** Use TCP for text */
	class MacClientTCPNetwork : public ClientTCPNetwork
	{
	//public:

	//	MacClientTCPNetwork();
	//	virtual ~MacClientTCPNetwork();

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
	class MacClientUDPNetwork : public ClientUDPNetwork
	{
	//public:

	//	MacClientUDPNetwork();
	//	virtual ~MacClientUDPNetwork();

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