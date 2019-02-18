#pragma once
#include "PacketTypes.h"
#include "boost/asio.hpp"
#include <vector>
#include <queue>


using namespace boost::asio;

class PacketMapper
{
public:
	~PacketMapper();
	static PacketMapper* getInstance();
	void Enqueue(const ip::udp::endpoint, const std::vector<unsigned char>);
	void MapReceivedPackets();
private:
	void Map(const ip::udp::endpoint, std::vector<unsigned char>) const;
	PacketMapper();
	std::queue<std::pair<const ip::udp::endpoint, const std::vector<unsigned char>>> packet_queue;
	static PacketMapper* instance;
};

