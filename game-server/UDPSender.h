#pragma once
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "Client.h"
#include <vector>
#include <algorithm>

using namespace boost::asio;

class UDPSender
{
public:
	static UDPSender* getInstance();
	~UDPSender();
	void Poll();
	void SendDataToClient(std::shared_ptr<Client> client, std::vector<unsigned char> data);
private:
	UDPSender();
	io_service ioservice;
	ip::udp::socket scket;
	static UDPSender* instance;
	void write_handler(const boost::system::error_code& error, std::size_t bytes_transferred);
};

