#include "Client.h"

unsigned short Client::id_counter = 0;

void Client::SetId()
{
	if (id == 0)
	{
		id = Client::GetNextId();
	}
}

const unsigned short Client::GetId() const
{
	return id;
}