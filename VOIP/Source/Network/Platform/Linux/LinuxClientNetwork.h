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

		void SetClientUsername(std::string Username);
		std::string GetClientUsername() const { return m_ClientUsername; }

	private:

		std::string m_ClientUsername;
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