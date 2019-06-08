#pragma once
#include "voippch.h"

#if VOIP_PLATFORM_WINDOWS
// TODO: Move this stuff into the source file if we can (forward decl)

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#endif

namespace VOIP {

	enum class EConnectionStatus
	{
		CS_CONNECTING,
		CS_CONNECTED,
		CS_DISCONNECTING,
		CS_DISCONNECTED,
		CS_CONNECTERROR,
		CS_DISCONNECTERROR,
	};

	/** Use TCP for text */
	class TCPNetwork
	{
	public:
		TCPNetwork();
		TCPNetwork(const std::string& host, uint16 port);
		virtual ~TCPNetwork();

		std::string GetHost() const { return m_host; }
		uint16 GetPort() const { return m_port; }

#if VOIP_PLATFORM_WINDOWS

		struct sockaddr_in GetHostAsSockAddr() const;

#endif

		void SetHost(const std::string& host);
		void SetPort(uint16 port);

		std::string GetIdentifier() const { return m_host + ":" + std::to_string(m_port); }

		// Maybe send a string&?
		virtual void SendChatMessage(char* Message) = 0;


		// TODO: Another implementation that can disconnect us from a current server before connecting to another
		virtual void Connect() = 0;

		// TODO: Another implementation that takes in an ip:port as the identifier for the server and disconnects specifically from it if we're connected
		virtual void Disconnect() = 0;

	protected:

		std::string m_host;
		uint16 m_port;

		EConnectionStatus m_ConnectionStatus;

#if VOIP_PLATFORM_WINDOWS

		struct sockaddr_in m_hostsocket;

#endif
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
		virtual void Connect() = 0;

		// TODO: Another implementation that takes in an ip:port as the identifier for the server and disconnects specifically from it if we're connected
		virtual void Disconnect() = 0;

	protected:

		std::string m_host;
		uint16 m_port;

		EConnectionStatus m_ConnectionStatus;
	};
}

