#pragma once
#include "boost/asio.hpp"
#include <vector>

using namespace boost::asio;

class UDPSender
{
public:
	static UDPSender* getInstance();
	~UDPSender();

	void SendDataToClient(std::string message);

private:
	UDPSender();
	io_service ioservice;
	ip::udp::socket scket;
	ip::udp::endpoint endpoint;
	const char* clientIp = "127.0.0.1";
	const unsigned short clientPort = 1235;
	static UDPSender* instance;
};

