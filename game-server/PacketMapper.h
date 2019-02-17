#pragma once
#include "PacketTypes.h"
#include "boost/asio.hpp"
#include <vector>


using namespace boost::asio;

class PacketMapper
{
public:
	~PacketMapper();
	static PacketMapper* getInstance();
	void Map(const ip::udp::endpoint, std::vector<unsigned char>) const;

private:
	PacketMapper();
	static PacketMapper* instance;
};

