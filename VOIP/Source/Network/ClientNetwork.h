#pragma once
#include "Network/Network.h"


namespace VOIP {

	class ClientTCPNetwork : public TCPNetwork
	{
	public:

		ClientTCPNetwork();
		virtual ~ClientTCPNetwork();

		void Connect() override;
		void Disconnect() override;

	private:
		bool bConnected;
	};

	class ClientUDPNetwork : public UDPNetwork
	{

	};
}