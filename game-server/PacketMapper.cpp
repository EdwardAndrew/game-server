#include "PacketMapper.h"
#include "ConnectionHandler.h"

PacketMapper* PacketMapper::instance;

PacketMapper* PacketMapper::getInstance() {
	if (instance == nullptr) instance = new PacketMapper();
	return instance;
}

void PacketMapper::Map(const std::vector<unsigned char> packet)
{
	switch (static_cast<PacketTypes>(packet[0])) {
		case PacketTypes::CLIENT_REQUEST_CONNECT:
			ConnectionHandler::getInstance()->ClientRequestConnection(packet);
			break;
		case PacketTypes::CLIENT_ACCEPTS_CHALLENGE:
			ConnectionHandler::getInstance()->ClientAcceptChallenge(packet);
			break;
		case PacketTypes::CLIENT_KEEP_ALIVE:
			ConnectionHandler::getInstance()->ClientAcknowledgeKeepAlive(packet);
			break;
		default:
			fprintf(stderr, "Failed to map incoming packet\n");
			break;
	}
}

PacketMapper::PacketMapper()
{
}

PacketMapper::~PacketMapper()
{
}
