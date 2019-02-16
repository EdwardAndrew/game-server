#pragma once
#include "boost/asio.hpp"
#include "ClientState.h"
using namespace boost::asio;

struct Client
{
	ip::udp::endpoint endpoint;
	ClientState clientState = ClientState::DISCONNECTED;

	bool operator==(const Client& rhs) const
	{
		return (endpoint.address().to_string() == rhs.endpoint.address().to_string());
	}
	bool operator!=(const Client& rhs) const
	{
		return !operator==(rhs);
	}
};

