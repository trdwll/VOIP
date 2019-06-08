
#ifdef VOIP_PLATFORM_WINDOWS

#include <Network/ServerNetwork.h>
#include <memory.h>
#include <string.h>

int main()
{
	VOIP::Logger::Init();

	VOIP::ServerTCPNetwork* server_tcp_connection = new VOIP::ServerTCPNetwork();
	//std::shared_ptr<VOIP::ServerTCPNetwork> server_tcp_connection = std::make_shared<VOIP::ServerTCPNetwork>();
	server_tcp_connection->SetHost("localhost");
	server_tcp_connection->SetPort(10005);

	server_tcp_connection->Connect();
}

#endif