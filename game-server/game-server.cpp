#include <iostream>
#include "UDPSender.h"
#include "UDPReceiver.h"

int main()
{

	UDPReceiver* rec = new UDPReceiver();

	rec->Read();

	while (true)
	{
		rec->Poll();
		Sleep(1);
	}


	delete rec;
}
