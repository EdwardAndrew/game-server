#pragma once
#include "Client.h"
#include "ClientState.h"
#include "boost/asio.hpp"
#include <vector>
#include <algorithm>
#include <tuple>

using namespace boost::asio;
using std::for_each;
using std::begin;
using std::end;


class ConnectionHandler
{
public:
	static ConnectionHandler* getInstance();
	~ConnectionHandler();

	void ClientRequestConnection(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet);

	void ClientAcceptChallenge(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const;

	void ClientAcknowledgeKeepAlive(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const;

	void ClientSentSnapshot(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const;

	const std::vector<std::shared_ptr<Client>> GetClients() const { return clients; }

	void Step(float deltaTime);

private:
	ConnectionHandler();
	static ConnectionHandler* instance;

	std::vector<std::shared_ptr<Client>> clients;

	const std::tuple<bool, std::shared_ptr<Client>> getClientByEndpoint(const ip::udp::endpoint) const;
};

