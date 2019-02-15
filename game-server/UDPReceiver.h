#pragma once
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/array.hpp"
#include <algorithm>

using namespace boost::asio;

class UDPReceiver
{
public:
	UDPReceiver();
	~UDPReceiver();

	void Read();
	void Poll();


private: 	
	boost::array<char, 1024> recv_buffer;
	io_service ioservice;
	ip::udp::socket scket;
	ip::udp::endpoint endpoint;

	const char* xPlaneServerIp = "127.0.0.1";
	const unsigned short xPlaneServerPort = 1234;

	void read_handler(const boost::system::error_code, size_t);
};

