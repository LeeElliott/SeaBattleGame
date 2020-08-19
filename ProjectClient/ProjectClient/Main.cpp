#pragma once

#include "Game.h"
#include "Input.h"

#include <windows.h>


// Values may change
#define WORLD_WIDTH 4096;
#define WORLD_HEIGHT 4096;

void processInput(sf::RenderWindow* hwnd, Input* input)
{
	sf::Event event;
	while (hwnd->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			hwnd->close();
			break;
		case sf::Event::Resized:
			hwnd->setView(sf::View(sf::FloatRect(0, 0,
				event.size.width, event.size.height)));
			break;
		case sf::Event::KeyPressed:
			// Update input class
			input->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			// Update input class
			input->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			// Update input class
			input->setMouseXY(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			// LEFT
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// Update input class
				input->setMouseLeftDown(true);
			}

			//RIGHT
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				// Update input class
				input->setMouseRightDown(true);
			}
			break;
		case sf::Event::MouseButtonReleased:
			// LEFT
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// Update input class
				input->setMouseLeftDown(false);
			}

			// RIGHT
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				// Update input class
				input->setMouseRightDown(false);
			}
			break;
		default:
			// don't handle other events
			break;
		}		
	}

	// If Esc is pressed
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		hwnd->close();
	}
}

void main(int argc, char** argv[])
{
	srand(time(NULL));
	
	sf::RenderWindow window(sf::VideoMode(640, 352), "Pirates.io");

	Input input;
	
	Game game(&window, &input);

	sf::Clock clock;
	float deltaTime;

	while (window.isOpen())
	{
		// Main loop
		processInput(&window, &input);
		deltaTime = clock.restart().asSeconds();

		game.Update(deltaTime);
		game.Render();
	}
}
