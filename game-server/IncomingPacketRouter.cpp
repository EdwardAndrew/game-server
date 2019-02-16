#include "IncomingPacketRouter.h"

IncomingPacketRouter* IncomingPacketRouter::instance;

IncomingPacketRouter* IncomingPacketRouter::getInstance() {
	if (instance == nullptr) instance = new IncomingPacketRouter();
	return instance;
}

void IncomingPacketRouter::Map(const std::vector<unsigned char> request)
{
	switch (static_cast<MessageTypes>(request[0])) {
	case MessageTypes::CLIENT_REQUEST_CONNECT:
		std::cout << "Cleint requests connection" << std::endl;
		break;
	}
}

IncomingPacketRouter::IncomingPacketRouter()
{
}

IncomingPacketRouter::~IncomingPacketRouter()
{
}
