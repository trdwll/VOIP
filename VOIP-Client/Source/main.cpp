

#include <Network/ClientNetwork.h>

#include <memory.h>
#include <string.h>

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ClientTCPNetwork> client_tcp_connection(VOIP::TCPNetwork::CreateClientTCPNetwork());

	// std::shared_ptr<VOIP::ClientTCPNetwork> client_tcp_connection = std::make_shared<VOIP::ClientTCPNetwork>();
	// client_tcp_connection->SetClientUsername("TestUsername");

	client_tcp_connection->SetHost("localhost");
	client_tcp_connection->SetPort(10006);

	if (client_tcp_connection->Connect())
	{
		// do magic
	}

	std::cin.ignore(); // basically a pause or wait (press enter to continue)
	//std::cout << "Type: ";
	//char* msg = "";
	//std::cin >> msg;

	//client_tcp_connection->SendChatMessage(msg);
}

