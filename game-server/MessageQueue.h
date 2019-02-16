#pragma once
#include <queue>

class MessageQueue
{
public:
	MessageQueue();
	~MessageQueue();

	void Enqueue(std::string message);
	std::string Dequeue();

private:
	std::queue<std::string> queue;
};

