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

void MessageQueue::Enqueue(const Client client, const std::vector<unsigned char> message)
{
	queue.push(std::pair<Client, std::vector<unsigned char>>(client, message));
}

void MessageQueue::Enqueue(const Client client, const void * data, const size_t size)
{
	std::vector<unsigned char> buffer(sizeof(size));
	std::memcpy(buffer.data(), &data, sizeof(size));

	queue.push(std::pair<Client, std::vector<unsigned char>>(client, buffer));
}

std::pair<Client, std::vector<unsigned char>> MessageQueue::Dequeue()
{
	std::pair<Client, std::vector<unsigned char>> value = queue.front();
	queue.pop();

	return value;
}
