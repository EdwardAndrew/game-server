#include "MessageQueue.h"

MessageQueue* MessageQueue::instance;

MessageQueue* MessageQueue::getInstance() {
	if (instance == nullptr) instance = new MessageQueue();
	return instance;
}

MessageQueue::MessageQueue()
{
	std::mutex mtx;
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::Enqueue(const std::shared_ptr<Client> client, const std::vector<unsigned char> message)
{
	mtx.lock();
	queue.push(std::pair<std::shared_ptr<Client>, std::vector<unsigned char>>(client, message));
	mtx.unlock();
}

void MessageQueue::Enqueue(const std::shared_ptr<Client> client, const void * data, const size_t size)
{
	std::vector<unsigned char> buffer(sizeof(size));
	std::memcpy(buffer.data(), &data, sizeof(size));

	mtx.lock();
	queue.push(std::pair<std::shared_ptr<Client>, std::vector<unsigned char>>(client, buffer));
	mtx.unlock();
}

std::pair<std::shared_ptr<Client>, std::vector<unsigned char>> MessageQueue::Dequeue()
{
	mtx.lock();
	std::pair<std::shared_ptr<Client>, std::vector<unsigned char>> value = queue.front();
	queue.pop();
	mtx.unlock();

	return value;
}
