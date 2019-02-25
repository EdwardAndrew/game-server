#include "Config.h"
#include "UDPCommunication.h"
#include "MessageQueue.h"
#include "PacketMapper.h"
#include "ConnectionHandler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "glm/vec3.hpp"

bool running = true;

using Time = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using float_sec = std::chrono::duration<float>;
using float_time_point = std::chrono::time_point<Time, float_sec>;
std::mutex mtx;

void incomingStream() {
	mtx.lock();
	auto receive = std::shared_ptr<UDPCommunication>(UDPCommunication::getInstance());
	mtx.unlock();
	receive->Read();
	while (running)
	{
		sleep(1);
	}
}

void outgoingStream() {
	mtx.lock();
	auto sender = std::shared_ptr<UDPCommunication>(UDPCommunication::getInstance());
	mtx.unlock();
	auto queue = std::shared_ptr<MessageQueue>(MessageQueue::getInstance());

	while (running)
	{
		while (!queue->isEmpty())
		{

			auto clientMessage = queue->Dequeue();
			sender->SendDataToClient(clientMessage.first, clientMessage.second);
			sender->Poll();
		}
		sender->Poll();
		sleep(1);
	}
}

void waitForStopCommand()
{
	fprintf(stdout, "Server is running, enter STOP to quit\n");
	while (running) {
		sleep(100);
		std::string input;
		std::cin >> input;
		if (input == "STOP" || input == "stop" || input == "s" || input == "Stop") running = false;
	}
}

int main()
{
	auto connectionHandler = std::shared_ptr<ConnectionHandler>(ConnectionHandler::getInstance());
	auto messageQueue = std::shared_ptr<MessageQueue>(MessageQueue::getInstance());
	std::thread incomingThread(incomingStream);
	std::thread outgoingThread(outgoingStream);
	std::thread waitForStopCommandThread(waitForStopCommand);

	float elapsedTime = 0.0f;
	float deltaTime = 0.0f;
	float lastTickTime = 0.0f;
	auto start = Time::now();
	while (running)
	{
		if (elapsedTime - lastTickTime > (1.0f/TICKRATE))
		{		
			connectionHandler->Step(deltaTime);
			auto clients = connectionHandler->GetClients();
			for(auto client : clients)
			{ 
				if (client->clientState != ClientState::CONNECTED) continue;

				std::vector<unsigned char> packet;
				packet.push_back(PacketTypes::SERVER_CLIENT_SNAPSHOT);
				packet.push_back(static_cast<unsigned char>(clients.size() - 1));
				packet.push_back(static_cast<unsigned char>(client->GetId()));
				auto clientPlayerSnapshot = client->player->GetSnapshot();
				packet.insert(packet.end(), clientPlayerSnapshot.begin(), clientPlayerSnapshot.end());
				
				//fprintf(stdout, "%s\n", client->player->ToString().c_str());

				for (auto otherClient : clients) {
					if (otherClient == client) continue;
					auto playerSnapshot = otherClient->player->GetSnapshot();
					packet.push_back(static_cast<unsigned char>(otherClient->GetId()));
					packet.insert(packet.end(), playerSnapshot.begin(), playerSnapshot.end());
				}
				messageQueue->Enqueue(client, packet);
			}
			lastTickTime = elapsedTime;
		}
		float_sec d = (Time::now() - start);
		deltaTime = d.count() - elapsedTime;
		elapsedTime = d.count();

		//int msUntilNextTick = static_cast<unsigned char>(floor((((1.0f / TICKRATE) - (elapsedTime - lastTickTime))*1000)-0.5f));
		//if (msUntilNextTick > 0)
		//{
		//	sleep(msUntilNextTick);
		//}
	}
	outgoingThread.join();
	incomingThread.join();
	waitForStopCommandThread.join();

	return 0;
}
