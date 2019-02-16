#include <iostream>
#include "UDPSender.h"
#include "UDPReceiver.h"
#include <thread>

bool running = true;

void incomingStream()
{
	UDPReceiver* receiver = UDPReceiver::getInstance();
	receiver->Read();

	while (running)
	{
		receiver->Poll();
		Sleep(1);
	}
}

void outgoingStream() {
	UDPSender* sender = UDPSender::getInstance();

	while (running)
	{
		Sleep(10);
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

	while (running)
	{
		// Game Logic
	}

	outgoingThread.join();
	incomingThread.join();
	waitForStopCommandThread.join();

	return 0;
}
