#include "UDPReceiver.h"
#include "PacketMapper.h"


UDPReceiver* UDPReceiver::instance;

UDPReceiver* UDPReceiver::getInstance() {
	if (instance == nullptr) instance = new UDPReceiver();
	return instance;
}

void UDPReceiver::read_handler(const boost::system::error_code error, size_t bytes_transferred) {
	std::vector<unsigned char> data;
	std::copy(std::begin(recv_buffer), std::begin(recv_buffer) + bytes_transferred, std::back_inserter(data));

	PacketMapper::getInstance()->Map(data);

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
	scket.async_receive(boost::asio::buffer(recv_buffer),
		boost::bind(&UDPReceiver::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

UDPReceiver::~UDPReceiver()
{
	scket.close();
	ioservice.stop();
}