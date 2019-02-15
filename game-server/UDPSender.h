#pragma once
#include "boost/asio.hpp"
#include <vector>

using namespace boost::asio;

class UDPSender
{
public:
	UDPSender();
	~UDPSender();

	void SendData(std::vector<char> message);

private:
	io_service ioservice;
	ip::udp::socket scket;
	ip::udp::endpoint endpoint;
	const char* serverIp = "127.0.0.1";
	const unsigned short serverPort = 1235;
};

