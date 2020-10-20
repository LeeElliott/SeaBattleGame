#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include "Sprite.h"
#include "Input.h"
#include "EnemyManager.h"

class Player : public Sprite
{
public:
	Player();
	~Player();

	void update(float dt);
	void setInput(Input* in);
	void setWindow(sf::RenderWindow* hwnd) { window = hwnd; }
	void setCentre(sf::Vector2f c) { screenCentre = c; }
	void setEnemyMan(EnemyManager* eM) { eManager = eM; }
	sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b);

protected:
	void destroyed();
	void checkCollision();
	bool enemyCollision(int i);
	sf::Vector2f generateUnitVector(float angle);

	Input* input;
	sf::RenderWindow* window;
	EnemyManager* eManager;

	sf::Vector2f position, screenCentre;
};

#endif // PLAYER_H
