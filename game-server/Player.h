#pragma once

#include <vector>
#include "glm/vec3.hpp"
#include "PacketTypes.h"

class Player
{
public:
	Player();
	~Player();

	void MapClientSnapshot(std::vector<unsigned char> snapshot_packet);

	const std::vector<unsigned char> GetSnapshot();

private:
	glm::vec3 position;
	glm::vec3 rotation;

};

