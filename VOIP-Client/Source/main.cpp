
#ifdef VOIP_PLATFORM_WINDOWS

#include <Network/ClientNetwork.h>
#include <memory.h>
#include <string.h>

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ClientTCPNetwork> client_tcp_connection = std::make_shared<VOIP::ClientTCPNetwork>();
	client_tcp_connection->SetHost("localhost");
	client_tcp_connection->SetPort(10005);

	client_tcp_connection->Connect();

	std::cout << "Type: ";
	char* msg = "";
	std::cin >> msg;

	client_tcp_connection->SendChatMessage(msg);
}

#endif