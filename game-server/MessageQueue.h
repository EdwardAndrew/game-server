#pragma once
#include "Client.h"
#include <queue>
#include <vector>
#include <mutex>

class MessageQueue
{
public:
	static MessageQueue* getInstance();

	~MessageQueue();

	void Enqueue(const std::shared_ptr<Client> client, const std::vector<unsigned char> message);
	void Enqueue(const std::shared_ptr<Client> client, const void* data, const size_t size);
	bool isEmpty() const { return queue.empty(); }

	std::pair<std::shared_ptr<Client>, std::vector<unsigned char>> Dequeue();

private:
	std::mutex mtx;
	static MessageQueue* instance;
	MessageQueue();
	std::queue<std::pair<std::shared_ptr<Client>, std::vector<unsigned char>>> queue;
};

