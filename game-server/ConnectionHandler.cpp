#include "ConnectionHandler.h"
#include "MessageQueue.h"
#include "PacketTypes.h"

ConnectionHandler* ConnectionHandler::instance;

ConnectionHandler * ConnectionHandler::getInstance()
{
	if (instance == nullptr) instance = new ConnectionHandler();
	return instance;
}

void ConnectionHandler::ClientRequestConnection(const std::vector<unsigned char> packet) const
{
	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_CHALLENGE_CLIENT);

	fprintf(stdout, "Server Challenge client\n");
	MessageQueue::getInstance()->Enqueue(response);
}

void ConnectionHandler::ClientAcceptChallenge(const std::vector<unsigned char> packet) const
{
	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_ACCEPT_CLIENT);

	fprintf(stdout, "Server Accepts Client\n");
	MessageQueue::getInstance()->Enqueue(response);
}

void ConnectionHandler::ClientAcknowledgeKeepAlive(const std::vector<unsigned char> packet) const
{
	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_ACKNOWLEDGE_ALIVE);

	fprintf(stdout, "Server Acknoledges Client is alive\n");
	MessageQueue::getInstance()->Enqueue(response);
}

ConnectionHandler::ConnectionHandler()
{
}
ConnectionHandler::~ConnectionHandler()
{
}