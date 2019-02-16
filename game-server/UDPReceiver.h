#pragma once
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/array.hpp"
#include <algorithm>

using namespace boost::asio;

class UDPReceiver
{
public:
	static UDPReceiver* getInstance();
	~UDPReceiver();

	void Read();
	void Poll();

private: 
	static UDPReceiver* instance;
	boost::array<char, 1024> recv_buffer;
	io_service ioservice;
	ip::udp::socket scket;
	ip::udp::endpoint endpoint;

	const unsigned short listenPort = 1234;

	UDPReceiver();
	void read_handler(const boost::system::error_code, size_t);
};

