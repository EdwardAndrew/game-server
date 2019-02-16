#include <iostream>
#include "UDPSender.h"
#include "UDPReceiver.h"
#include "MessageQueue.h"
#include <thread>
#include <mutex>
#include <chrono>
#include "glm/vec3.hpp"

bool running = true;
std::mutex mtx;

void incomingStream()
{
	
	std::shared_ptr<UDPReceiver> receiver = std::shared_ptr<UDPReceiver>(UDPReceiver::getInstance());
	receiver->Read();

	while (running)
	{
		receiver->Poll();
		Sleep(1);
	}
}

void outgoingStream() {
	auto sender = std::shared_ptr<UDPSender>(UDPSender::getInstance());
	auto queue = std::shared_ptr<MessageQueue>(MessageQueue::getInstance());

	while (running)
	{
		while (!queue->isEmpty())
		{
			mtx.lock();
			std::vector<unsigned char> data = queue->Dequeue();
			sender->SendDataToClient(data);
			mtx.unlock();
		}
		sender->Poll();
		Sleep(1);
	}
}

void waitForStopCommand()
{
	std::cout << "Server is running, enter STOP to quit" << std::endl;
	while (running) {
		std::string input;
		std::cin >> input;
		if (input == "STOP" || input == "stop" || input == "s" || input == "Stop") running = false;
		Sleep(100);
	}
}

int main()
{
	std::thread incomingThread(incomingStream);
	std::thread outgoingThread(outgoingStream);
	std::thread waitForStopCommandThread(waitForStopCommand);

	glm::vec3 pos = glm::vec3(-0.0f, 0.0f, 0.0f);

	std::chrono::high_resolution_clock timer;
	float deltaTime = 0.0f;
	auto previousTime = timer.now();

	while (running)
	{
		if (deltaTime >= 1/10)
		{
			pos += glm::vec3(0.0f, 0.0f, 20.0f) * deltaTime;

			std::vector<unsigned char> data(sizeof(pos));
			std::memcpy(data.data(), &pos, sizeof(pos));
			
			mtx.lock();
			MessageQueue::getInstance()->Enqueue(data);
			mtx.unlock();
			previousTime = timer.now();
		}
		auto stop = timer.now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - previousTime).count() / 1000000.0f;
	}

	outgoingThread.join();
	incomingThread.join();
	waitForStopCommandThread.join();

	return 0;
}
