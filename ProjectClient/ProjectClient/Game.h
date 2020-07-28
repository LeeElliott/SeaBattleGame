#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Cursor.h"
#include "EnemyManager.h"
#include "NetworkManager.h"
#include "Input.h"
#include "Player.h"


class Game
{

public:
	Game(sf::RenderWindow* hwnd, Input* input);
	~Game();

	void Update(float deltaTime);
	void Render();

protected:
	enum GameState 
	{
		CONNECTED, UNCONNECTED
	};

	GameState currentState;
	sf::RenderWindow* window;

	Input* input;
	Cursor cursor;

	Player player;
	EnemyManager eManager;
	NetworkManager nManager;

	sf::Clock clock;
	float deltaTime;


	// Graphics
	sf::Texture splashTex;	// Used to show connection not yet made
	sf::Texture playerTex;
	sf::Texture cursorTex;
	sf::Texture backTex;

	sf::RectangleShape rect;

	sf::Vector2f position;
	float counter;
};

#endif // !GAME_H
