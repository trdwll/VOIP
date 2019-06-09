#pragma once
#include "Network/ServerNetwork.h"

namespace VOIP {

	/** Use TCP for text */
	class LinuxServerTCPNetwork : public ServerTCPNetwork
	{
	public:

		LinuxServerTCPNetwork();
		virtual ~LinuxServerTCPNetwork();

		void Connect() override;
		void Disconnect() override;
		void SendChatMessage(char* Message) override;

	};

	/** Use UDP for voice */
	class LinuxServerUDPNetwork : public ServerUDPNetwork
	{
	public:

		LinuxServerUDPNetwork();
		virtual ~LinuxServerUDPNetwork();

		void Connect() override;
		void Disconnect() override;

	};
}