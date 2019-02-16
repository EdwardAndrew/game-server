#include "MessageQueue.h"

MessageQueue::MessageQueue()
{
}


MessageQueue::~MessageQueue()
{
}

void MessageQueue::Enqueue(std::string message)
{
	queue.push(message);
}

std::string MessageQueue::Dequeue()
{
	std::string value = queue.front();
	queue.pop();

	return value;
}
