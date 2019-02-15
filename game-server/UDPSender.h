#pragma once
#include "boost/asio.hpp"

class UDPSender
{
public:
	UDPSender();
	~UDPSender();
private:
	const char* xPlaneServerIp = "127.0.0.1";
	const unsigned short xPlaneServerPort = 1234;
};

