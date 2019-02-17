#include "Player.h"

Player::Player()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

Player::~Player()
{

}

void Player::MapClientSnapshot(std::vector<unsigned char> snapshot_packet)
{
	float pX, pY, pZ, rX, rY, rZ;

	std::memcpy(&pX, &snapshot_packet[1], sizeof(float));
	std::memcpy(&pY, &snapshot_packet[5], sizeof(float));
	std::memcpy(&pZ, &snapshot_packet[9], sizeof(float));
	std::memcpy(&rX, &snapshot_packet[13], sizeof(float));
	std::memcpy(&rY, &snapshot_packet[17], sizeof(float));
	std::memcpy(&rZ, &snapshot_packet[21], sizeof(float));

	position = glm::vec3(pX, pY, pZ);
	rotation = glm::vec3(rX, rY, rZ);
}

const std::vector<unsigned char> Player::GetSnapshot()
{
	constexpr size_t snapshot_size = 
		sizeof(position) + 
		sizeof(rotation);

	std::vector<unsigned char> snapshot_bytes(snapshot_size);
	std::memcpy(&snapshot_bytes[0], &position[0], sizeof(position));
	std::memcpy(&snapshot_bytes[12], &rotation[0], sizeof(rotation));

	return snapshot_bytes;
}


