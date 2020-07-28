#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
	// Set up socket
	socket.setBlocking(false);

	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		// Error Message
		fprintf(stderr, "Error: Binding failed.\n");
	}

	// Store my port number
	myPort = socket.getLocalPort();
	std::string s = std::to_string(socket.getLocalPort());
	s += "\n";
	const char *c = s.c_str();
	fprintf(stderr, c);
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::updateEnemies(EnemyManager* eManager)
{
	sf::Packet received;
	sf::IpAddress sender;
	unsigned short port;
	
	if (socket.receive(received, sender, port) != sf::Socket::Done)
	{
		// fprintf(stderr, "Error: Receive failed.\n");
	}
	else
	{
		// Check packet type
		int packetType;
		received >> packetType;
		{
			if (packetType == 1)
			{
				int enemyCount;
				float positionX;
				float positionY;
				float sizeX;
				float sizeY;
				float originX;
				float originY;
				sf::Int32 id;
				float rotation;

				received >> enemyCount;
				for (int i = 0; i < enemyCount; i++)
				{
					received >> id >> positionX >> positionY >> sizeX >> sizeY >> originX >> originY >> rotation;

					if (id != myPort)
					{
						sf::Vector2f position = sf::Vector2f(positionX, positionY);
						sf::Vector2f size = sf::Vector2f(sizeX, sizeY);
						sf::Vector2f origin = sf::Vector2f(originX, originY);

						bool foundIt = false;
						for (size_t i = 0; i < eManager->enemies.size(); i++)
						{
							unsigned short ident = id;
							unsigned short enemIdent = eManager->enemies[i].getID();
							if (ident == enemIdent)
							{
								eManager->enemies[i].updateStatus(position, size, origin, rotation);

								foundIt = true;

								break;
							}
						}

						if (!foundIt)
						{
							int identifier = id;
							eManager->addEnemy(position, origin, size, identifier, rotation);
						}
					}
				}
			}
			else if (packetType == 2)
			{
				sf::String message;

				received >> message;

				std::string s = message;

				const char *c = s.c_str();
				fprintf(stderr, c);

				connected = false;
			}
		}
	}
}

void NetworkManager::updatePosition(Player * player)
{
	if (connected)
	{
		sf::Vector2f position = player->getPosition();
		sf::Vector2f size = player->getSize();
		sf::Vector2f origin = player->getOrigin();
		float rotation = player->getRotation();

		// Create packet of data
		sf::Packet data;
		data << position.x << position.y << size.x << size.y << origin.x << origin.y << rotation;

		// Send current status
		if (socket.send(data, SERVERIP, SERVERPORT) != sf::Socket::Done)
		{
			fprintf(stderr, "Error: Send failed.\n");
		}
	}
}
