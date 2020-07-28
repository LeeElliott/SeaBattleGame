#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "EnemyManager.h"
#include "Player.h"

// The IP address of the server
#define SERVERIP "127.0.0.1"

// The UDP port number on the server
#define SERVERPORT 4444

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

	void updateEnemies(EnemyManager* eManager);
	void updatePosition(Player* player);


protected:
	sf::UdpSocket socket;
	unsigned short myPort;
	bool connected = true;
};

#endif // !NETWORK_MANAGER_H
