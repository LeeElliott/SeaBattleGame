#include "Player.h"

Player::Player()
{
	// Set random starting position
	position.x = static_cast <float> (rand() % 2048);
	position.y = static_cast <float> (rand() % 2048);
	setPosition(position);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	// Ship moves towards position of clicked mouse
	// Turns are to be smooth using linear interpolation or similar
	if (input->isLeftDown())
	{
		position = getPosition();

		sf::Vector2f mouse_pos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

		sf::Vector2f newPosition = Lerp(position, mouse_pos);		

		// Rotate to face cursor
		const float PI = 3.14159265f;

		float dx = position.x - newPosition.x;
		float dy = position.y - newPosition.y;

		float rotation = (atan2(dy, dx)) * 180 / PI;
		setRotation(rotation + 180);

		if (newPosition.x < 0)
			newPosition.x = 2048;
		else if (newPosition.x > 2048)
			newPosition.x = 0;
		else if (newPosition.y < 0)
			newPosition.y = 2048;
		else if (newPosition.y > 2048)
			newPosition.y = 0;

		setPosition(newPosition);

		updateAABB();
	}
	
	checkCollision();
}

void Player::setInput(Input * in)
{
	input = in;
}



sf::Vector2f Player::Lerp(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f factor = 0.001f * (b - a);

	// Limit the max speed
	if (factor.x > 0.5f)
	{
		factor.x = 0.5f;
	}
	if (factor.x < -0.5f)
	{
		factor.x = -0.5f;
	}
	if (factor.y > 0.5f)
	{
		factor.y = 0.5f;
	}
	if (factor.y < -0.5f)
	{
		factor.y = -0.5f;
	}

	sf::Vector2f lerp = a + factor;

	return lerp;
}

void Player::destroyed()
{
	// Reset size
	setSize(sf::Vector2f(64.0f, 64.0));
	setSize(sf::Vector2f(64.0f, 64.0));
	setOrigin(sf::Vector2f(32.0f, 32.0f));

	// Move to random location
	position.x = static_cast <float> (rand() % 2048);
	position.y = static_cast <float> (rand() % 2048);
	setPosition(position);

}


void Player::checkCollision()
{
	for (size_t i = 0; i < eManager->enemies.size(); i++)
	{
		if (enemyCollision(i))
		{
			if (eManager->enemies[i].getActive())
			{
				if (eManager->enemies[i].getSize().x > getSize().x)
				{
					// Enemy bigger player dies
					// Resize and recentre
					// Reset size
					setSize(sf::Vector2f(64.0f, 64.0));
					setOrigin(sf::Vector2f(32.0f, 32.0f));
					// Teleport to random location
					position.x = static_cast <float> (rand() % 2048);
					position.y = static_cast <float> (rand() % 2048);
					setPosition(position);
				}
				else if (getSize().x > eManager->enemies[i].getSize().x)
				{
					// Player bigger enemy dies player grows
					// Resize and recentre
					float scaler = eManager->enemies[i].getSize().x / 8;

					setSize(sf::Vector2f(getSize().x + scaler, getSize().y + scaler));
					setOrigin(sf::Vector2f(getOrigin().x + (scaler / 2), getOrigin().y + (scaler / 2)));
				}
			}
		}
	}
}

bool Player::enemyCollision(int i)
{
	if (getAABB().left + getAABB().width < eManager->enemies[i].getAABB().left)
		return false;
	if (getAABB().left > eManager->enemies[i].getAABB().left + eManager->enemies[i].getAABB().width)
		return false;
	if (getAABB().top + getAABB().height < eManager->enemies[i].getAABB().top)
		return false;
	if (getAABB().top > eManager->enemies[i].getAABB().top + eManager->enemies[i].getAABB().height)
		return false;

	return true;
}

sf::Vector2f Player::generateUnitVector(float angle)
{
	// Generates a unit vector from provided angle
	sf::Vector2f vector;
	vector.x = cos(angle);
	vector.y = sin(angle);

	return vector;
}
