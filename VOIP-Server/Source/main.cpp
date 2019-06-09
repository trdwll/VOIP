
#ifdef VOIP_PLATFORM_WINDOWS
// #include <Network/Platform/Windows/WindowsServerNetwork.h>
#endif

#include <Network/ServerNetwork.h>

#include <memory.h>
#include <string.h>

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ServerTCPNetwork> server_tcp_connection = std::make_shared<VOIP::ServerTCPNetwork>();
	server_tcp_connection->SetHost("localhost");
	server_tcp_connection->SetPort(10006);

	server_tcp_connection->Connect();
}

