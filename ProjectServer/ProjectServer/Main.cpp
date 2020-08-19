#pragma once

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <sqlite3.h>

// The IP address of the server
#define SERVERIP "127.0.0.1"

// The UDP port number on the server
#define SERVERPORT 4444

// Function prototypes
void sendUpdate();
void receiveUpdate();

sf::UdpSocket socket;
int nextID = 0;
int maxClients = 50;

sf::Packet packet;

// Store Stats
int ports[50];
float positionX[50];
float positionY[50];
float sizeX[50];
float sizeY[50];
float originX[50];
float originY[50];
float rotation[50];

void main(int argc, char** argv[])
{


	socket.setBlocking(false);
	if (socket.bind(SERVERPORT) != sf::Socket::Done)
	{
		// Error Message
		fprintf(stderr, "Error: Binding failed.\n");
	}

	sf::Clock clock;
	float deltaTime;

	float delay = 0.4f;

	while (true)
	{
		deltaTime = clock.restart().asSeconds();
		
		receiveUpdate();			

		if (delay < 0.0f)
		{
			sendUpdate();
			delay = 0.4f;
		}
		else
		{
			delay -= deltaTime;
		}
	}
}

void sendUpdate()
{
	sf::Packet packet;

	// Add the size
	sf::Int32 clientCount = nextID;
	packet << 1 << clientCount;

	// Iterate to add data
	for (int i = 0; i < nextID; i++)
	{
		// Convert to sendable data
		sf::Int32 currentPort = sf::Int32(ports[i]); 

		packet << currentPort << positionX[i] << positionY[i] << sizeX[i] << sizeY[i] << originX[i] << originY[i] << rotation[i];
	}	

	// Send current status
	for (int i = 0; i < nextID; i++)
	{
		if (socket.send(packet, SERVERIP, ports[i]) != sf::Socket::Done)
		{
			fprintf(stderr, "Error: Send failed.\n");
		}
	}
}

void receiveUpdate()
{
	sf::Packet received;
	sf::IpAddress sender;
	unsigned short port;

	if (socket.receive(received, sender, port) != sf::Socket::Done)
	{
		// fprintf(stderr, "NOTHING RECEIVED.\n");
	}
	else
	{
		float posX;
		float posY;
		float sX;
		float sY;
		float orX;
		float orY;
		float rot;

		received >> posX >> posY >> sX >> sY >> orX >> orY >> rot;

		int currentPort = port;

		bool foundIt = false;
		for (int i = 0; i < nextID; i++)
		{
			if (currentPort == ports[i])
			{
				// If already joined
				positionX[i] = posX; 
				positionY[i] = posY;
				sizeX[i] = sX;
				sizeY[i] = sY;
				originX[i] = orX;
				originY[i] = orY;
				rotation[i] = rot;
				foundIt = true;
			}
		}

		if (!foundIt)
		{
			if (nextID < maxClients)
			{
				ports[nextID] = currentPort;
				positionX[nextID] = posX;
				positionY[nextID] = posY;
				sizeX[nextID] = sX;
				sizeY[nextID] = sY;
				originX[nextID] = orX;
				originY[nextID] = orY;
				rotation[nextID] = rot;
				nextID++;
			}
			else
			{
				// Send full message
				sf::String message = "Server full please try again later or continue to play offline. \n";

				packet << 2 << message;

				if (socket.send(packet, SERVERIP, currentPort) != sf::Socket::Done)
				{
					fprintf(stderr, "Error: Send failed.\n");
				}
			}
		}
	}
}
