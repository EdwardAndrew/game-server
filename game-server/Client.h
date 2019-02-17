#pragma once
#include "ClientState.h"
#include "Player.h"
#include "Config.h"
#include "boost/asio.hpp"

using namespace boost::asio;

class Client
{
public:
	
	Client()
		: player{ std::unique_ptr<Player>(new Player()) }
		, id {GetNextId()}
		{};

	ip::udp::endpoint endpoint;
	ClientState clientState = ClientState::DISCONNECTED;
	std::unique_ptr<Player> player;
	const unsigned short id;

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

	void Step(const float deltaTime) {
		timeSinceLastPacketReceived += deltaTime;
	}

	std::string ToString() {
		return endpoint.address().to_string() + ":" + std::to_string(endpoint.port());
	}

private:
	float timeSinceLastPacketReceived = 0.0f;
	static unsigned short id_counter;
	static const unsigned short GetNextId() { id_counter++; return id_counter; };
};

