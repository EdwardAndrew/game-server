#include "IncomingPacketRouter.h"

IncomingPacketRouter* IncomingPacketRouter::instance;

IncomingPacketRouter* IncomingPacketRouter::getInstance() {
	if (instance == nullptr) instance = new IncomingPacketRouter();
	return instance;
}

void IncomingPacketRouter::Map(std::string request)
{
	std::cout << request.c_str() << std::endl;
}

IncomingPacketRouter::IncomingPacketRouter()
{
}

IncomingPacketRouter::~IncomingPacketRouter()
{
}
