#pragma once

#include "Game.h"


Game::Game(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
	currentState = UNCONNECTED;
	input->setMouseLeftDown(false);

	sf::View view(sf::Vector2f(320, 176), sf::Vector2f(640, 352));
	window->setView(view);
	window->setMouseCursorVisible(false);

	// Load background
	backTex.loadFromFile("gfx/Background.png");
	rect.setSize(sf::Vector2f(2730.0f, 2730.0f));
	rect.setPosition(sf::Vector2f(-341.0f, -341.0f));
	rect.setTexture(&backTex);

	// Load player
	playerTex.loadFromFile("gfx/playership.png");
	player.setSize(sf::Vector2f(64.0f, 64.0f));
	player.setOrigin(32.0f, 32.0f);
	player.setTexture(&playerTex);
	player.setInput(in);
	player.setWindow(window);
	player.setEnemyMan(&eManager);

	// Load cursor
	cursorTex.loadFromFile("gfx/cursor.png");
	cursor.setSize(sf::Vector2f(32, 32));
	cursor.setTexture(&cursorTex);
	cursor.setPosition(400, 300);
	cursor.passInput(in);

	counter = 0.2f;
}

Game::~Game() 
{

}

void Game::Update(float deltaTime)
{
	// Update view
	sf::View temp = window->getView();
	temp.setCenter(player.getPosition());
	window->setView(temp);
	
	// Calculate delta time. How much time has passed since it was last calculated(in seconds) and restart the clock.
	deltaTime = clock.restart().asSeconds();

	// Update objects	
	cursor.setCentre(temp.getCenter());
	cursor.update(deltaTime);
	player.update(deltaTime);
	eManager.update(deltaTime);
	
	if (counter < 0.0f)
	{
		// Check network messages
		nManager.updateEnemies(&eManager);

		// Send network message
		nManager.updatePosition(&player);
		counter = 0.2f;
	}
	else
	{
		counter -= deltaTime;
	}

	if (input->isKeyDown(sf::Keyboard::A))
	{
		input->setKeyUp(sf::Keyboard::A);

		// Display coords
		std::string s = std::to_string(player.getPosition().x);
		s += ", ";
		s += std::to_string(player.getPosition().y);
		s += "\n";
		const char *c = s.c_str();
		fprintf(stderr, c);
	}
}
	
void Game::Render()
{
	// Clear screen to sea blue
	//window->clear(sf::Color::Color(0, 105, 148, 255));
	window->clear(sf::Color::Color(0, 0, 0, 255));

	// Render scene
	window->draw(rect);

	window->draw(player);
	window->draw(cursor);
	eManager.render(window);
	

	// Display on screen
	window->display();
}

