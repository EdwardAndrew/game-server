#pragma once
#include <vector>

class ConnectionHandler
{
public:
	static ConnectionHandler* getInstance();
	~ConnectionHandler();

	void ClientRequestConnection(const std::vector<unsigned char> packet) const;

	void ClientAcceptChallenge(const std::vector<unsigned char> packet) const;

	void ClientAcknowledgeKeepAlive(const std::vector<unsigned char> packet) const;

private:
	ConnectionHandler();
	static ConnectionHandler* instance;
};

