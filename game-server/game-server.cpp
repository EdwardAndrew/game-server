#include <iostream>
#include "UDPSender.h"
#include "UDPReceiver.h"

int main()
{

	//UDPReceiver* rec = new UDPReceiver();

	//rec->Read();

	//while (true)
	//{
	//	rec->Poll();
	//	Sleep(1);
	//}


	//delete rec;

	UDPSender* sender = new UDPSender();

	for (int i = 0; i < 4; i++)
	{
		std::string data = std::string("Test Message");
		sender->SendDataToClient(data);
	}

	delete sender;
}
