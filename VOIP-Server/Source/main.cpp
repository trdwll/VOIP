
#include <Network/ServerNetwork.h>

#include <memory.h>
#include <string.h>

#ifdef VOIP_PLATFORM_WINDOWS
#include <WinSock2.h>
#endif


#ifdef VOIP_PLATFORM_WINDOWS
void MessageReceived(class VOIP::ServerTCPNetwork* Listener, SOCKET socketID, std::string message)
#elif defined(VOIP_PLATFORM_LINUX) || defined(VOIP_PLATFORM_MAC)
void MessageReceived(class VOIP::ServerTCPNetwork* Listener, int32 socketID, std::string message)
#endif
{
	std::string strOut = "SOCKET #" + std::to_string(socketID) + ": " + message + "\r";
	Listener->SendChatMessageTo(strOut, socketID);
	
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
			if (inputstr == "exit")
			{
				break;
			}

			inputstr += "\n";
			server_tcp->SendChatMessageTo(inputstr, NULL);
		}
	}
}

