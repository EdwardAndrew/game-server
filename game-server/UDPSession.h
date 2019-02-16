#pragma once
#include "boost/asio.hpp"
#include "boost/array.hpp"
#include <iostream>
#include <vector>

using namespace::boost::asio;

struct UDPSession
{
	ip::udp::endpoint remote_endpoint;
	boost::array<char, 1024> recv_buffer;

	void handle_request(const boost::system::error_code error, size_t bytes_transferred) {
		std::string data;
		std::copy(std::begin(recv_buffer), std::begin(recv_buffer) + bytes_transferred, std::back_inserter(data));
		std::cout << "Request: " << data.c_str() << std::endl;
	}
};

