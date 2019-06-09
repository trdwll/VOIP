#pragma once
#include "voippch.h"

#include "Network/Network.h"

namespace VOIP {

	/** Use TCP for text */
	class ServerTCPNetwork : public TCPNetwork
	{
	public:
		ServerTCPNetwork();
		virtual ~ServerTCPNetwork();
	};

	/** Use UDP for voice */
	class ServerUDPNetwork : public UDPNetwork
	{
	public:
		ServerUDPNetwork();
		virtual ~ServerUDPNetwork();
	};
}

