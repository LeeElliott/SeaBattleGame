#ifndef GAME_H
#define GAME_H

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Cursor.h"
#include "EnemyManager.h"
#include "NetworkManager.h"
#include "ProjectileManager.h"
#include "Input.h"
#include "Player.h"


class Game
{

public:
	Game(sf::RenderWindow* hwnd, Input* input);
	~Game();

	void Update(float deltaTime);
	void Render();

	void RenderUI();

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
	ProjectileManager pManager;

	sf::Clock clock;
	float deltaTime;
	sf::Font font;

	// Graphics
	sf::Texture splashTex;	// Used to show connection not yet made
	sf::Texture playerTex;
	sf::Texture cursorTex;
	sf::Texture backTex;
	sf::Texture shotTex;

	sf::RectangleShape rect;

	sf::Vector2f position;
	float counter;

	// Hud text
	sf::Text positionText;
	sf::Text rotationText;
	sf::Text angleText;
	sf::Text forwardText;
};

#endif // !GAME_H
