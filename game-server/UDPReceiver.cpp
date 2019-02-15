#include "UDPReceiver.h"

void UDPReceiver::read_handler(const boost::system::error_code error, size_t bytes_transferred) {
	fprintf(stderr, "Error %s", error.message().c_str());
	fprintf(stderr, "Code %d", error.value());
	Read();
}

void UDPReceiver::Poll() {
	ioservice.poll();
}

UDPReceiver::UDPReceiver() 
	: scket(ioservice)
{
	scket = ip::udp::socket(ioservice, ip::udp::endpoint(ip::udp::v4(), xPlaneServerPort));
	ip::udp::endpoint endpoint(ip::address_v4::from_string(xPlaneServerIp), xPlaneServerPort);
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
}