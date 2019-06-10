
#include <Network/ServerNetwork.h>
#include <Network/Platform//Windows/WindowsServerNetwork.h>

#include <memory.h>
#include <string.h>
#include <WinSock2.h>

class ServerTCPNetwork;

void MessageReceived(ServerTCPNetwork* Listener, SOCKET socketID, std::string message)
{
	std::string strOut = "SOCKET #" + std::to_string(socketID) + ": " + message + "\r";
	// Listener->SendChatMessageTo(strOut, socketID);
	//Listener->GetHost();

	//logging msg in the server
	std::cout << "SOCKET " << socketID << ": " << message << "\r";
}

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ServerTCPNetwork> server_tcp(VOIP::Network::CreateServerTCPNetwork());
	server_tcp->SetHost("127.0.0.1");
	server_tcp->SetPort(DEFAULT_PORT);
	server_tcp->SetCallback((VOIP::ServerMessageReceivedHandler)MessageReceived);

	if (server_tcp->Connect())
	{
		std::string inputstr;

		while (true)
		{
			std::getline(std::cin, inputstr);
			if (inputstr == "exit") break;

			inputstr += "\n";
			server_tcp->SendChatMessageTo(inputstr, NULL);
		}
	}
}

