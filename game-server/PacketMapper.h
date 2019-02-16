#pragma once
#include <iostream>
#include <vector>
#include "PacketTypes.h"

class PacketMapper
{
public:
	~PacketMapper();
	static PacketMapper* getInstance();
	void Map(std::vector<unsigned char>);

private:
	PacketMapper();
	static PacketMapper* instance;
};

