#pragma once
#include "boost/asio.hpp"
#include "ClientState.h"
#include "Player.h"
using namespace boost::asio;

struct Client
{
public:
	
	Client()
		: player{ std::unique_ptr<Player>(new Player()) }
		{};

	ip::udp::endpoint endpoint;
	ClientState clientState = ClientState::DISCONNECTED;
	std::unique_ptr<Player> player;

	bool operator==(const Client& rhs) const
	{
		return (endpoint.address().to_string() == rhs.endpoint.address().to_string());
	}
	bool operator!=(const Client& rhs) const
	{
		return !operator==(rhs);
	}
};

