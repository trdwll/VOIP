#pragma once
#include "Network/ClientNetwork.h"

namespace VOIP {

	/** Use TCP for text */
	class LinuxClientTCPNetwork : public ClientTCPNetwork
	{
	public:

		LinuxClientTCPNetwork();
		virtual ~LinuxClientTCPNetwork();

		void Connect() override;
		void Disconnect() override;

		void SendChatMessage(char* Message) override;

	private:
	};

	/** Use UDP for voice */
	class LinuxClientUDPNetwork : public ClientUDPNetwork
	{
	public:

		LinuxClientUDPNetwork();
		virtual ~LinuxClientUDPNetwork();

		void Connect() override;
		void Disconnect() override;
	};
}