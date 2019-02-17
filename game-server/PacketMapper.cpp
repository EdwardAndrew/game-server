#include "PacketMapper.h"
#include "ConnectionHandler.h"

PacketMapper* PacketMapper::instance;

PacketMapper* PacketMapper::getInstance() {
	if (instance == nullptr) instance = new PacketMapper();
	return instance;
}

void PacketMapper::Map(const ip::udp::endpoint endpoint, std::vector<unsigned char> packet) const
{
	switch (static_cast<PacketTypes>(packet[0])) {
		case PacketTypes::CLIENT_REQUEST_CONNECT:
			ConnectionHandler::getInstance()->ClientRequestConnection(endpoint, packet);
			break;
		case PacketTypes::CLIENT_ACCEPTS_CHALLENGE:
			ConnectionHandler::getInstance()->ClientAcceptChallenge(endpoint, packet);
			break;
		case PacketTypes::CLIENT_KEEP_ALIVE:
			ConnectionHandler::getInstance()->ClientAcknowledgeKeepAlive(endpoint, packet);
			break;
		case PacketTypes::CLIENT_SERVER_SNAPSHOT:
			ConnectionHandler::getInstance()->ClientSentSnapshot(endpoint, packet);
			break;
		case PacketTypes::CLIENT_REQUEST_GAMESTATE:
			ConnectionHandler::getInstance()->ClientRequestGamestate(endpoint, packet);
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
