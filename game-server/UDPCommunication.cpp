#include "Config.h"
#include "UDPCommunication.h"
#include "PacketMapper.h"
UDPCommunication* UDPCommunication::instance;

UDPCommunication* UDPCommunication::getInstance()
{
	if (instance == nullptr) instance = new UDPCommunication();
	return instance;
}

void UDPCommunication::write_handler(const boost::system::error_code& error, std::size_t bytes_transferred)
{
}

UDPCommunication::UDPCommunication()
	:scket(ioservice)
{
	scket = ip::udp::socket(ioservice, ip::udp::endpoint(ip::udp::v4(), SERVER_PORT));
}

void UDPCommunication::read_handler(const boost::system::error_code error, size_t bytes_transferred) 
{

	std::vector<unsigned char> data;
	std::copy(std::begin(recv_buffer), std::begin(recv_buffer) + bytes_transferred, std::back_inserter(data));
	PacketMapper::getInstance()->Enqueue(endpoint, data);
	Read();
}

void UDPCommunication::SendDataToClient(const std::shared_ptr<Client> client, const std::vector<unsigned char> message)
{
	if (sizeof(message) >= 1024)
	{
		throw std::exception("Message too large to fit in buffer");
	}

	scket.async_send_to(buffer(&message[0], message.size()), client->endpoint, 0,
		boost::bind(&UDPCommunication::write_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void UDPCommunication::Read()
{
	scket.async_receive_from(boost::asio::buffer(recv_buffer), endpoint,
		boost::bind(&UDPCommunication::read_handler, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void UDPCommunication::Poll()
{
	ioservice.reset();
	ioservice.poll();
}

UDPCommunication::~UDPCommunication()
{
	scket.close();
	ioservice.stop();
}
