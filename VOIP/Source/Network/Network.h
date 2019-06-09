#pragma once
#include "voippch.h"

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

		std::string GetIdentifier() const { return m_host + ":" + std::to_string(m_port); }
	
	public:
		/** Virtual Methods */

		virtual void Connect() = 0;
		virtual void Disconnect() = 0;

	protected:
		/** Variables */

		std::string m_host;
		uint16 m_port;

		EConnectionStatus m_ConnectionStatus;
	};

	// Whatever's defined here can be accessible via server or client so beware
	class TCPNetwork : public Network 
	{
	public:

		virtual void SendChatMessage(char* Message) = 0;
	};

	// Whatever's defined here can be accessible via server or client so beware
	class UDPNetwork : public Network {};
}

