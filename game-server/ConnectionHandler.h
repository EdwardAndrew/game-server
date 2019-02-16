#pragma once
#include "boost/asio.hpp"
#include "Client.h"
#include "ClientState.h"
#include <vector>
#include <algorithm>
#include <tuple>

using namespace boost::asio;

class ConnectionHandler
{
public:
	static ConnectionHandler* getInstance();
	~ConnectionHandler();

	void ClientRequestConnection(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet);

	void ClientAcceptChallenge(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const;

	void ClientAcknowledgeKeepAlive(const ip::udp::endpoint endpoint, const std::vector<unsigned char> packet) const;

private:
	ConnectionHandler();
	static ConnectionHandler* instance;

	std::vector<Client> clients;

	const std::tuple<bool, Client> getClientByEndpoint(const ip::udp::endpoint) const;
};

