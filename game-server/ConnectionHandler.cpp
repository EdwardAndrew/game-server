#include "ConnectionHandler.h"
#include "MessageQueue.h"
#include "PacketTypes.h"

ConnectionHandler* ConnectionHandler::instance;

ConnectionHandler * ConnectionHandler::getInstance()
{
	if (instance == nullptr) instance = new ConnectionHandler();
	return instance;
}

void ConnectionHandler::ClientRequestConnection(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet)
{
	Client requestedClient;
	int port = endpoint.port();
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple))
	{
		requestedClient = std::get<1>(clientTuple);
	}
	else
	{
		requestedClient.endpoint = endpoint;
		requestedClient.clientState = ClientState::REQUESTED_CONNECTION;
		clients.push_back(requestedClient);
	}

	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_CHALLENGE_CLIENT);

	fprintf(stdout, "Server Challenge client\n");
	MessageQueue::getInstance()->Enqueue(requestedClient, response);
}

void ConnectionHandler::ClientAcceptChallenge(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const
{
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple) == false) {
		fprintf(stderr, "The client that accepted the challenge is not registered");
		return;
	}

	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_ACCEPT_CLIENT);

	fprintf(stdout, "Server Accepts Client\n");
	MessageQueue::getInstance()->Enqueue(std::get<1>(clientTuple), response);

}

const std::tuple<bool, Client> ConnectionHandler::getClientByEndpoint(const ip::udp::endpoint endpoint) const
{
	const Client dummyValue;
	auto found = std::find_if(std::begin(clients), std::end(clients), 
		[endpoint](Client client){
			Client newClient;
			newClient.endpoint = endpoint;
			return client == newClient;
		});

	return found != clients.end() ? std::tuple<bool, Client>(true,*found) : std::tuple<bool, Client>(false, dummyValue);

}

void ConnectionHandler::ClientAcknowledgeKeepAlive(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const
{
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple) == false) {
		fprintf(stderr, "The Keep Alive message came from a client not registered.");
		return;
	}

	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_ACKNOWLEDGE_ALIVE);

	MessageQueue::getInstance()->Enqueue(std::get<1>(clientTuple), response);
}

ConnectionHandler::ConnectionHandler()
{
}
ConnectionHandler::~ConnectionHandler()
{
}