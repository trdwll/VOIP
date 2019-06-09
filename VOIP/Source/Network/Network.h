#pragma once
#include "voippch.h"

#ifdef VOIP_PLATFORM_WINDOWS
#include <winsock2.h>
#endif

/**
 * Abstract class that all Networking classes should be derived from
 */
namespace VOIP {

	typedef void(*ClientMessageReceivedHandler)(std::string message);

#ifdef VOIP_PLATFORM_WINDOWS
	typedef void(*ServerMessageReceivedHandler)(class TCPNetwork* Listener, SOCKET socketID, std::string message);
#elif VOIP_PLATFORM_LINUX
	typedef void(*ServerMessageReceivedHandler)(class TCPNetwork* Listener, int32 socketID, std::string message);
#endif

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

		// this only needs to be on the client
		ClientMessageReceivedHandler m_ClientMessageReceivedEvent;

		// this only needs to be on the server 
		ServerMessageReceivedHandler m_ServerMessageReceivedEvent;
	};

	// Whatever's defined here can be accessible via server or client so beware
	class TCPNetwork : public Network 
	{
	public:

#ifdef VOIP_PLATFORM_WINDOWS
		/** Send a message to all clients. */
		//virtual void SendChatMessage(const std::string& Message) = 0;

		/** Send a message to a specific client. */
		//virtual void SendChatMessage(const std::string& Message, SOCKET ClientSocket) = 0;
#elif VOIP_PLATFORM_LINUX

#endif 
	};

	// Whatever's defined here can be accessible via server or client so beware
	class UDPNetwork : public Network {};
}

