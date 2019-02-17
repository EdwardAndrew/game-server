#pragma once
#include "boost/asio.hpp"
#include "ClientState.h"
#include "Player.h"
#include "Config.h"

using namespace boost::asio;

class Client
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

	void PacketReceived() { timeSinceLastPacketReceived = 0.0f; }

	const float GetTimeSinceLastPacketReceived() const { return timeSinceLastPacketReceived; }

	const bool HasTimedOut() const { return timeSinceLastPacketReceived >= CLIENT_TIMEOUT; }

	void Step(float deltaTime) {
		timeSinceLastPacketReceived += deltaTime;
	}

private:
	float timeSinceLastPacketReceived = 0.0f;

};

