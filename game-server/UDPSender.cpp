#include "UDPSender.h"

UDPSender* UDPSender::instance;

UDPSender* UDPSender::getInstance()
{
	if (instance == nullptr) instance = new UDPSender();
	return instance;
}

void UDPSender::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	//fprintf(st, "Wrote %d bytes.", bytes_transferred);
}

UDPSender::UDPSender()
	:scket(ioservice)
{

	scket.open(ip::udp::v4());
	endpoint = ip::udp::endpoint(ip::address_v4::from_string(clientIp), clientPort);
}

void UDPSender::SendDataToClient(const std::vector<unsigned char> message) 
{
	if (message.size() > 1024)
	{
		throw std::exception("Message too large to fit in buffer");
	}

	scket.async_send_to(buffer(&message[0], message.size()), endpoint, 0,
		boost::bind(&UDPSender::write_handler, this, 
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

UDPSender::~UDPSender()
{
	scket.close();
	ioservice.stop();
}

void UDPSender::Poll()
{
	ioservice.poll();
}
