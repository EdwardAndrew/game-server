#include "Config.h"
#include "UDPSender.h"
#include "UDPReceiver.h"
#include "MessageQueue.h"
#include "ConnectionHandler.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "glm/vec3.hpp"


bool running = true;

using Time = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using float_sec = std::chrono::duration<float>;
using float_time_point = std::chrono::time_point<Time, float_sec>;

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
	fprintf(stdout, "Server is running, enter STOP to quit\n");
	while (running) {
		Sleep(100);
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
				std::vector<unsigned char> packet;
				if (client->clientState != ClientState::CONNECTED) continue;

				packet.push_back(PacketTypes::SERVER_CLIENT_SNAPSHOT);
				packet.push_back((unsigned char)(clients.size() - 1));
				packet.push_back((unsigned char)client->id);
				auto clientPlayerSnapshot = client->player->GetSnapshot();
				packet.insert(packet.end(), clientPlayerSnapshot.begin(), clientPlayerSnapshot.end());
				
				for (auto otherClient : clients) {
					if (otherClient == client) continue;
					auto playerSnapshot = otherClient->player->GetSnapshot();
					packet.push_back((unsigned char)otherClient->id);
					packet.insert(packet.end(), playerSnapshot.begin(), playerSnapshot.end());
				}
				messageQueue->Enqueue(client, packet);
			}
			lastTickTime = elapsedTime;
		}
		float_sec d = (Time::now() - start);
		deltaTime = d.count() - elapsedTime;
		elapsedTime = d.count();

		int msUntilNextTick = (int)floor((((1.0f / TICKRATE) - (elapsedTime - lastTickTime))*1000)-0.5f);
		if (msUntilNextTick > 0)
		{
			Sleep(msUntilNextTick);
		}
	}
	outgoingThread.join();
	incomingThread.join();
	waitForStopCommandThread.join();

	return 0;
}
