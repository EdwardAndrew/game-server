#pragma once
#include <queue>
#include <vector>
#include "Client.h"

class MessageQueue
{
public:
	static MessageQueue* getInstance();

	~MessageQueue();

	void Enqueue(const Client client, const std::vector<unsigned char> message);
	void Enqueue(const Client client, const void* data, const size_t size);
	bool isEmpty() const { return queue.empty(); }

	std::pair<Client, std::vector<unsigned char>> Dequeue();

private:
	static MessageQueue* instance;
	MessageQueue();
	std::queue<std::pair<Client, std::vector<unsigned char>>> queue;
};

