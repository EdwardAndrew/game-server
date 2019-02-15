#include "UDPSender.h"

UDPSender* UDPSender::instance;

UDPSender* UDPSender::getInstance()
{
	if (instance == nullptr) instance = new UDPSender();
	return instance;
}


void handler(const boost::system::error_code& error, std::size_t bytes_transferred) {
	fprintf(stderr, "Error %s", error.message().c_str());
	fprintf(stderr, "Code %d", error.value());
}

UDPSender::UDPSender()
	:scket(ioservice)
{
	scket.open(ip::udp::v4());
	endpoint = ip::udp::endpoint(ip::address_v4::from_string(clientIp), clientPort);
}

void UDPSender::SendDataToClient(std::string message) 
{
	std::vector<char> data(message.c_str(), message.c_str() + message.size() + 1u);

	scket.async_send_to(boost::asio::buffer(data, data.size()), endpoint, 0, handler);
}

UDPSender::~UDPSender()
{
	scket.close();
}
