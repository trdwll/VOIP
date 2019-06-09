
#include <Network/ServerNetwork.h>

#include <memory.h>
#include <string.h>
#include <WinSock2.h>

void MessageReceived(class TCPNetwork* Listener, SOCKET socketID, std::string message)
{
	std::string strOut = "SOCKET #" + std::to_string(socketID) + ": " + message + "\r";
	// Listener->SendChatMessage(strOut, socketID);

	//logging msg in the server
	std::cout << "SOCKET " << socketID << ": " << message << "\r";
}

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ServerTCPNetwork> server_tcp_connection(VOIP::Network::CreateServerTCPNetwork());
	server_tcp_connection->SetHost("localhost");
	server_tcp_connection->SetPort(10006);

	if (server_tcp_connection->Connect())
	{
		std::string inputstr;

		while (true)
		{
			std::getline(std::cin, inputstr);
			if (inputstr == "exit") break;

			inputstr += "\n";
			server_tcp_connection->SendChatMessage("Hey man", NULL);
		}
	}
}

