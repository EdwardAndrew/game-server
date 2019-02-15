#include <iostream>
#include "UDPSender.h"
#include "UDPReceiver.h"


int main()
{

	UDPReceiver* receiver = UDPReceiver::getInstance();
	UDPSender* sender = UDPSender::getInstance();

	receiver->Read();

	while (true)
	{
		receiver->Poll();
		Sleep(1);
	}
}
