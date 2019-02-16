#include "UDPReceiver.h"
#include "PacketMapper.h"
#include <iostream>

UDPReceiver* UDPReceiver::instance;

UDPReceiver* UDPReceiver::getInstance() {
	if (instance == nullptr) instance = new UDPReceiver();
	return instance;
}

void UDPReceiver::read_handler(const boost::system::error_code error, size_t bytes_transferred) {
	std::vector<unsigned char> data;
	std::copy(std::begin(recv_buffer), std::begin(recv_buffer) + bytes_transferred, std::back_inserter(data));

	std::cout << endpoint.address().to_string().c_str() << ":";
	std::cout << endpoint.port() << std::endl;



	PacketMapper::getInstance()->Map(endpoint, data);

	Read();
}

void UDPReceiver::Poll() {
	ioservice.poll();
}

UDPReceiver::UDPReceiver() 
	: scket(ioservice)
{
	scket = ip::udp::socket(ioservice, ip::udp::endpoint(ip::udp::v4(), listenPort));
}

void UDPReceiver::Read()
{
	scket.async_receive_from(boost::asio::buffer(recv_buffer), endpoint,
		boost::bind(&UDPReceiver::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

UDPReceiver::~UDPReceiver()
{
	scket.close();
	ioservice.stop();
}