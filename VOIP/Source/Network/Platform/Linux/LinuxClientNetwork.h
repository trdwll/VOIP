#pragma once
#include "Network/ClientNetwork.h"

namespace VOIP {

	/** Use TCP for text */
	class LinuxClientTCPNetwork : public ClientTCPNetwork
	{
	public:

		LinuxClientTCPNetwork();
		virtual ~LinuxClientTCPNetwork();

		bool Connect() override;
		void Disconnect() override;

		void SendChatMessage(const std::string& Message) override;

		/** Create the receive thread */
		void ListenReceiveThread(MessageReceivedHandler handler) override;

		/** Receive the content from the thread */
		bool Receive(MessageReceivedHandler handler) override;

	private:
		bool Init() override;
	};

	/** Use UDP for voice */
	class LinuxClientUDPNetwork : public ClientUDPNetwork
	{
	public:

		LinuxClientUDPNetwork();
		virtual ~LinuxClientUDPNetwork();

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