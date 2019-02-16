#pragma once

enum PacketTypes {
	CLIENT_REQUEST_CONNECT = 40,
	CLIENT_ACCEPTS_CHALLENGE,
	CLIENT_KEEP_ALIVE,
	CLIENT_SERVER_SNAPSHOT = 50,

	SERVER_CHALLENGE_CLIENT = 70,
	SERVER_ACCEPT_CLIENT,
	SERVER_ACKNOWLEDGE_ALIVE,
	SERVER_CLIENT_SNAPSHOT = 80,
};