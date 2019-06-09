
#include <Network/ServerNetwork.h>

#include <memory.h>
#include <string.h>

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ServerTCPNetwork> server_tcp_connection(VOIP::Network::CreateServerTCPNetwork());
	server_tcp_connection->SetHost("localhost");
	server_tcp_connection->SetPort(10006);

	server_tcp_connection->Connect();
}

