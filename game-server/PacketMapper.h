#pragma once
#include "boost/asio.hpp"
#include <iostream>
#include <vector>
#include "PacketTypes.h"

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

