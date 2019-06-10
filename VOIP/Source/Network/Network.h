#pragma once
#include "voippch.h"

#ifdef VOIP_PLATFORM_WINDOWS
#include <winsock2.h>
#endif

/**
 * Abstract class that all Networking classes should be derived from
 */
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

	class Network
	{
	public:
		Network();
		Network(const std::string& host, uint16 port);
		virtual ~Network();

		static class ServerTCPNetwork* CreateServerTCPNetwork();
		static class ServerUDPNetwork* CreateServerUDPNetwork();

		static class ClientTCPNetwork* CreateClientTCPNetwork();
		static class ClientUDPNetwork* CreateClientUDPNetwork();

	public:
		/** Getters and Setters */
		
		std::string GetHost() const { return m_host; }
		uint16 GetPort() const { return m_port; }

		EConnectionStatus GetConnectionStatus() const { return m_ConnectionStatus; }

		void SetHost(const std::string& host);
		void SetPort(uint16 port);

		bool IsPortValid(uint16 port) const;
		//bool IsHostValid(const std::string& host) const;

		std::string GetIdentifier() const { return m_host + ":" + std::to_string(m_port); }
	
	public:
		/** Virtual Methods */

		virtual bool Connect() = 0;
		virtual void Disconnect() = 0;

	private:
		virtual bool Init() = 0;

	protected:
		/** Variables */

		std::string m_host;
		uint16 m_port;

		EConnectionStatus m_ConnectionStatus;

	};

	// Whatever's defined here can be accessible via server or client so beware
	class TCPNetwork : public Network { };

	// Whatever's defined here can be accessible via server or client so beware
	class UDPNetwork : public Network { };
}

