

#include <Network/ClientNetwork.h>

#include <memory.h>
#include <string.h>

void MsgRecv(std::string Message) 
{
	std::cout << "MSG: " << Message << std::endl;
}

int main()
{
	VOIP::Logger::Init();

	std::shared_ptr<VOIP::ClientTCPNetwork> client_tcp(VOIP::TCPNetwork::CreateClientTCPNetwork());

	// SClientData* ClientData;
	// client_tcp_connection->SetClientData(&ClientData);

	client_tcp->SetHost("localhost");
	client_tcp->SetPort(10006);

	if (client_tcp->Connect())
	{
		client_tcp->ListenReceiveThread(MsgRecv);

		std::string inputstr;
		while (true)
		{
			std::getline(std::cin, inputstr);
			if (inputstr == "exit")
			{
				break;
			}

			client_tcp->SendChatMessage(inputstr);
		}
	}

	std::cin.ignore(); // basically a pause or wait (press enter to continue)
}

