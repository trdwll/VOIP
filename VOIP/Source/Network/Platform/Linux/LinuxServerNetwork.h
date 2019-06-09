#pragma once
#include "Network/ServerNetwork.h"

namespace VOIP {

	/** Use TCP for text */
	class LinuxServerTCPNetwork : public ServerTCPNetwork
	{
	public:

		LinuxServerTCPNetwork();
		virtual ~LinuxServerTCPNetwork();

		bool Connect() override;
		void Disconnect() override;
		void SendChatMessage(const std::string& Message) override;

	private:
		bool Init() override;
	};

	/** Use UDP for voice */
	class LinuxServerUDPNetwork : public ServerUDPNetwork
	{
	public:

		LinuxServerUDPNetwork();
		virtual ~LinuxServerUDPNetwork();

		bool Connect() override;
		void Disconnect() override;

	private:
		bool Init() override;
	};
}