#pragma once
#include <iostream>
#include <vector>
#include "MessageTypes.h"

class IncomingPacketRouter
{
public:
	~IncomingPacketRouter();
	static IncomingPacketRouter* getInstance();
	void Map(std::vector<unsigned char>);

private:
	IncomingPacketRouter();
	static IncomingPacketRouter* instance;
};

