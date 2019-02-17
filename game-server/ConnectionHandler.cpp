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
	auto requestedClient = std::shared_ptr<Client>(new Client());
	int port = endpoint.port();
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple))
	{
		requestedClient = std::shared_ptr<Client>(std::get<1>(clientTuple));
	}
	else
	{
		requestedClient->endpoint = endpoint;
		requestedClient->clientState = ClientState::REQUESTED_CONNECTION;
		clients.push_back(requestedClient);
	}

	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_CHALLENGE_CLIENT);
	requestedClient->clientState = ClientState::CHALLENGED;
	requestedClient->PacketReceived();

	fprintf(stdout, "Server Challenge client\n");
	MessageQueue::getInstance()->Enqueue(requestedClient, response);
}

void ConnectionHandler::ClientAcceptChallenge(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const
{
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple) == false) {
		fprintf(stderr, "The client that accepted the challenge is not registered\n");
		return;
	}

	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_ACCEPT_CLIENT);

	std::get<1>(clientTuple)->clientState = ClientState::CONNECTED;
	std::get<1>(clientTuple)->PacketReceived();

	fprintf(stdout, "Server Accepts Client\n");

	MessageQueue::getInstance()->Enqueue(std::get<1>(clientTuple), response);
}

void ConnectionHandler::ClientAcknowledgeKeepAlive(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const
{
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple) == false) {
		fprintf(stderr, "The Keep Alive message came from a client not registered.");
		return;
	}

	std::get<1>(clientTuple)->clientState = ClientState::CONNECTED;
	std::get<1>(clientTuple)->PacketReceived();

	std::vector<unsigned char> response;
	response.push_back(PacketTypes::SERVER_ACKNOWLEDGE_ALIVE);

	MessageQueue::getInstance()->Enqueue(std::get<1>(clientTuple), response);
}

void ConnectionHandler::ClientSentSnapshot(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const
{
	auto clientTuple = getClientByEndpoint(endpoint);
	if (std::get<0>(clientTuple) == false) {
		fprintf(stderr, "The Snapshot came from a client not registered.\n");
		return;
	}

	std::get<1>(clientTuple)->PacketReceived();
	std::get<1>(clientTuple)->player->MapClientSnapshot(packet);
}

const std::tuple<bool, std::shared_ptr<Client>> ConnectionHandler::getClientByEndpoint(const ip::udp::endpoint endpoint) const
{
	const std::shared_ptr<Client> dummyValue;
	auto found = std::find_if(std::begin(clients), std::end(clients),
		[endpoint](std::shared_ptr<Client> client) {
		auto newClient = std::unique_ptr<Client>(new Client());
		newClient->endpoint = endpoint;
		return *client == *newClient;
	});

	return found != clients.end() ? std::tuple<bool, std::shared_ptr<Client>>(true, *found) : std::tuple<bool, std::shared_ptr<Client>>(false, dummyValue);

}

void ConnectionHandler::Step(float deltaTime)
{
	std::vector<std::shared_ptr<Client>> timedOutClients;

	for_each(begin(clients), end(clients), [deltaTime, timedOutClients](std::shared_ptr<Client> client) mutable {
		client->Step(deltaTime);
		if (client->HasTimedOut()) {
			timedOutClients.push_back(client);
			// TODO: Remove timed out client from clients list.
		}
	});

}

ConnectionHandler::ConnectionHandler()
{
}
ConnectionHandler::~ConnectionHandler()
{
}