#pragma once
#include "Client.h"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/array.hpp"
#include <vector>
#include <algorithm>

using namespace boost::asio;

class UDPCommunication
{
public:
	static UDPCommunication* getInstance();
	~UDPCommunication();
	void Read();
	void Poll();
	void SendDataToClient(std::shared_ptr<Client> client, std::vector<unsigned char> data);
private:
	static UDPCommunication* instance;
	boost::array<char, 1024> recv_buffer;
	io_service ioservice;
	ip::udp::socket scket;
	ip::udp::endpoint endpoint;
	UDPCommunication();
	void read_handler(const boost::system::error_code, size_t);
	void write_handler(const boost::system::error_code&, std::size_t);
};


