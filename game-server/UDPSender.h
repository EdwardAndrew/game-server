#pragma once
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include <vector>
#include <algorithm>

using namespace boost::asio;

class UDPSender
{
public:
	static UDPSender* getInstance();
	~UDPSender();
	void Poll();
	void SendDataToClient(std::vector<unsigned char> data);
private:
	UDPSender();
	io_service ioservice;
	ip::udp::socket scket;
	ip::udp::endpoint endpoint;
	const char* clientIp = "127.0.0.1";
	const unsigned short clientPort = 1235;
	static UDPSender* instance;
	void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
};

