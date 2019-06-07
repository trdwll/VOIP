#pragma once
#include "voippch.h"

namespace VOIP {

	/** Use TCP for text */
	class TCPNetwork
	{
	public:
		TCPNetwork();
		TCPNetwork(const std::string& host, uint16 port);
		virtual ~TCPNetwork();

		std::string GetHost() const { return m_host; }
		uint16 GetPort() const { return m_port; }

		void SetHost(const std::string& host);
		void SetPort(uint16 port);

		std::string GetIdentifier() const { return m_host + ":" + std::to_string(m_port); }

		// TODO: Another implementation that can disconnect us from a current server before connecting to another
		virtual void Connect();

		// TODO: Another implementation that takes in an ip:port as the identifier for the server and disconnects specifically from it if we're connected
		virtual void Disconnect();

	private:

		std::string m_host;
		uint16 m_port;

	};

	/** Use UDP for voice */
	class UDPNetwork
	{
	public:
		UDPNetwork();
		UDPNetwork(const std::string& host, uint16 port);
		virtual ~UDPNetwork();

		std::string GetHost() const { return m_host; }
		uint16 GetPort() const { return m_port; }

		void SetHost(const std::string& host);
		void SetPort(uint16 port);

		std::string GetIdentifier() const { return m_host + ":" + std::to_string(m_port); }

		// TODO: Another implementation that can disconnect us from a current server before connecting to another
		virtual void Connect();

		// TODO: Another implementation that takes in an ip:port as the identifier for the server and disconnects specifically from it if we're connected
		virtual void Disconnect();

	private:

		std::string m_host;
		uint16 m_port;
	};
}

