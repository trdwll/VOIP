#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	/** Use TCP for text */
	class ClientTCPNetwork : public TCPNetwork
	{
	public:
		ClientTCPNetwork();
		virtual ~ClientTCPNetwork();
	};

	/** Use UDP for voice */
	class ClientUDPNetwork : public UDPNetwork
	{
	public:
		ClientUDPNetwork();
		virtual ~ClientUDPNetwork();
	};
}

