#include "UDPSender.h"

using namespace boost::asio;

void handler(const boost::system::error_code& error, // Result of operation.
	std::size_t bytes_transferred) {
	fprintf(stderr, "Error %s", error.message().c_str());
	fprintf(stderr, "Code %d", error.value());
}

UDPSender::UDPSender()
{
	io_service ioservice;
	ip::udp::socket scket(ioservice);
	scket.open(ip::udp::v4());
	ip::udp::endpoint endpoint(ip::address_v4::from_string(xPlaneServerIp), xPlaneServerPort);
	boost::system::error_code err;
	char one[] = "One";
	char two[] = "Two";
	char three[] = "Three";
	char four[] = "Four";
	char five[] = "Five";
	char six[] = "Six";

	scket.async_send_to(boost::asio::buffer(one, sizeof(one)), endpoint, 0, handler);
	scket.async_send_to(boost::asio::buffer(two, sizeof(two)), endpoint, 0, handler);
	scket.async_send_to(boost::asio::buffer(three, sizeof(three)), endpoint, 0, handler);
	scket.async_send_to(boost::asio::buffer(four, sizeof(four)), endpoint, 0, handler);
	scket.async_send_to(boost::asio::buffer(five, sizeof(five)), endpoint, 0, handler);
	scket.async_send_to(boost::asio::buffer(six, sizeof(six)), endpoint, 0, handler);

	scket.close();
}


UDPSender::~UDPSender()
{
}
