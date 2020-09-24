#pragma once

#include "Game.h"
#include <iostream>


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
	rect.setSize(sf::Vector2f(4500.0f, 4500.0f));
	rect.setPosition(sf::Vector2f(-202.0f, -202.0f));
	rect.setTexture(&backTex);

	// Load cannonball texture
	shotTex.loadFromFile("gfx/cannonball.png");

	// Load player
	playerTex.loadFromFile("gfx/playership.png");
	player.setSize(sf::Vector2f(64.0f, 64.0f));
	player.setOrigin(32.0f, 32.0f);
	player.setTexture(&playerTex);
	player.setInput(in);
	player.setWindow(window);
	player.setEnemyMan(&eManager);
	player.setProjectileMan(&pManager);
	
	// Load cursor
	cursorTex.loadFromFile("gfx/cursor.png");
	cursor.setSize(sf::Vector2f(32, 32));
	cursor.setTexture(&cursorTex);
	cursor.setPosition(400, 300);
	cursor.passInput(in);

	if (!font.loadFromFile("gfx/arial.ttf"))
	{
		std::cout << "Font could not be loaded";
	}

	positionText.setString("");
	positionText.setFont(font);
	positionText.setCharacterSize(19);
	positionText.setFillColor(sf::Color::Black);
	positionText.setPosition(3, 3);

	rotationText.setString("");
	rotationText.setFont(font);
	rotationText.setCharacterSize(19);
	rotationText.setFillColor(sf::Color::Black);
	rotationText.setPosition(600, 3);

	angleText.setString("");
	angleText.setFont(font);
	angleText.setCharacterSize(19);
	angleText.setFillColor(sf::Color::Black);
	angleText.setPosition(3, 3);

	forwardText.setString("");
	forwardText.setFont(font);
	forwardText.setCharacterSize(19);
	forwardText.setFillColor(sf::Color::Black);
	forwardText.setPosition(600, 3);

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
	pManager.Update(deltaTime);
	
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
	pManager.Render(window);
	
	// Render UI
	RenderUI();

	// Display on screen
	window->display();
}

void Game::RenderUI()
{
	sf::View view = window->getView();

	// Debug info
	positionText.setString("Position : (" + std::to_string(player.getPosition().x) + ", "
		+ std::to_string(player.getPosition().y) + ")");
	positionText.setPosition(view.getCenter().x - 317, view.getCenter().y - 173);

	rotationText.setString("Rotation : " + std::to_string(player.getRotation()) + " deg");
	rotationText.setPosition(view.getCenter().x + 105, view.getCenter().y - 173);

	//angleText.setString("Angle to mouse : " + std::to_string(player.getAngle()) + " deg");
	//angleText.setPosition(view.getCenter().x + 45, view.getCenter().y + 153);


	angleText.setString("Cannon Rot : " + std::to_string(pManager.getCR()) + " deg");
	angleText.setPosition(view.getCenter().x + 45, view.getCenter().y + 153);

	forwardText.setString("Forward : (" + std::to_string(player.getForward().x) + ", " 
	+ std::to_string(player.getForward().y) + ")");
	forwardText.setPosition(view.getCenter().x - 317, view.getCenter().y + 153);

	window->draw(positionText);
	window->draw(rotationText);
	window->draw(angleText);
	window->draw(forwardText);

	// 
}
