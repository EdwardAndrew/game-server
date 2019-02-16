#pragma once
#include <queue>

class MessageQueue
{
public:
	static MessageQueue* getInstance();

	~MessageQueue();

	void Enqueue(std::vector<unsigned char> message);
	void Enqueue(void* data, size_t size);
	bool isEmpty() { return queue.empty(); }

	std::vector<unsigned char> Dequeue();

private:
	static MessageQueue* instance;
	MessageQueue();
	std::queue<std::vector<unsigned char>> queue;
};

