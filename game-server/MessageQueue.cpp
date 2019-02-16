#include "MessageQueue.h"

MessageQueue* MessageQueue::instance;

MessageQueue* MessageQueue::getInstance() {
	if (instance == nullptr) instance = new MessageQueue();
	return instance;
}


MessageQueue::MessageQueue()
{
}


MessageQueue::~MessageQueue()
{
}

void MessageQueue::Enqueue(std::vector<unsigned char> message)
{
	queue.push(message);
}

void MessageQueue::Enqueue(void * data, size_t size)
{
	std::vector<unsigned char> buffer(sizeof(size));
	std::memcpy(buffer.data(), &data, sizeof(size));

	queue.push(buffer);
}

std::vector<unsigned char> MessageQueue::Dequeue()
{
	std::vector<unsigned char> value = queue.front();
	queue.pop();

	return value;
}
