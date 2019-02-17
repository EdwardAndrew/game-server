#include <iostream>
#include "UDPSender.h"
#include "UDPReceiver.h"
#include "MessageQueue.h"
#include "ConnectionHandler.h"
#include <thread>
#include <chrono>
#include "glm/vec3.hpp"
#include "Config.h"

bool running = true;

using ms = std::chrono::duration<float, std::milli>;

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
			auto clientMessage = queue->Dequeue();
			sender->SendDataToClient(clientMessage.first, clientMessage.second);
			sender->Poll();
		}
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
	auto connectionHandler = std::shared_ptr<ConnectionHandler>(ConnectionHandler::getInstance());
	auto messageQueue = std::shared_ptr<MessageQueue>(MessageQueue::getInstance());
	std::thread incomingThread(incomingStream);
	std::thread outgoingThread(outgoingStream);
	std::thread waitForStopCommandThread(waitForStopCommand);
	std::chrono::high_resolution_clock timer;
	float deltaTime = 0.0f;
	float timeSinceLastTick = 0.0f;
	while (running)
	{
		auto start = timer.now();
		if (timeSinceLastTick > (1.0f/5.0f))
		{		
			auto clients = connectionHandler->GetClients();
			for(auto client : clients)
			{ 
				std::vector<unsigned char> packet;
				if (client->clientState != ClientState::CONNECTED) continue;

				packet.push_back(PacketTypes::SERVER_CLIENT_SNAPSHOT);
				packet.push_back((unsigned char)(clients.size() - 1));
				auto clientPlayerSnapshot = client->player->GetSnapshot();
				packet.insert(packet.end(), clientPlayerSnapshot.begin(), clientPlayerSnapshot.end());
				
				for (auto otherClient : clients) {
					if (otherClient == client) continue;
					auto playerSnapshot = otherClient->player->GetSnapshot();
					packet.insert(packet.end(), playerSnapshot.begin(), playerSnapshot.end());
				}
				messageQueue->Enqueue(client, packet);
			}
			timeSinceLastTick = 0.0f;
		}

		connectionHandler->Step(deltaTime);

		deltaTime = std::chrono::duration_cast<ms>(timer.now() - start).count() / 1000;
		timeSinceLastTick += deltaTime;
	}
	outgoingThread.join();
	incomingThread.join();
	waitForStopCommandThread.join();

	return 0;
}
