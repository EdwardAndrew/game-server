#pragma once
#include "PacketTypes.h"
#include <vector>
#include "glm/vec3.hpp"

class Player
{
public:
	Player();
	~Player();

	void MapClientSnapshot(std::vector<unsigned char> snapshot_packet);

	const std::vector<unsigned char> GetSnapshot();

	const std::string ToString() const;

	glm::vec3 position;
	glm::vec3 rotation;

};

