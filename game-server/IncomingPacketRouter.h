#pragma once
#include <iostream>

class IncomingPacketRouter
{
public:
	~IncomingPacketRouter();
	static IncomingPacketRouter* getInstance();
	void Map(std::string);

private:
	IncomingPacketRouter();
	static IncomingPacketRouter* instance;
};

