#include "Player.h"

Player::Player()
{
	// Set random starting position
	position.x = static_cast <float> (rand() % 4096);
	position.y = static_cast <float> (rand() % 4096);
	setPosition(position);

	moveSpeed = 64.0f;
	turnSpeed = 30.0f;
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

		sf::Vector2f newPosition = PositionLerp(dt);

		// Rotate to face cursor
		float newRotation = RotationLerp(newPosition, mouse_pos, getRotation(), dt);

		if (newPosition.x < 0)
			newPosition.x = 4096;
		else if (newPosition.x > 4096)
			newPosition.x = 0;
		else if (newPosition.y < 0)
			newPosition.y = 4096;
		else if (newPosition.y > 4096)
			newPosition.y = 0;

		setPosition(newPosition);
		setRotation(newRotation);

		updateAABB();
	}

	checkCollision();
}

void Player::setInput(Input * in)
{
	input = in;
}



sf::Vector2f Player::PositionLerp(float dt)
{
	sf::Vector2f currentPosition = getPosition();

	// Calculate forward vector
	forward.x = cosf((getRotation() * 3.14159265359) / 180);
	forward.y = sinf((getRotation() * 3.14159265359) / 180);

	sf::Vector2f lerp = currentPosition + ((forward * moveSpeed) * dt);

	return lerp;
}

float Player::RotationLerp(sf::Vector2f cp, sf::Vector2f mp, float r, float dt)
{
	float newRotation = r;
	sf::Vector2f target;

	// Calculate forward vector
	forward.x = cosf((r * 3.14159265359) / 180);
	forward.y = sinf((r * 3.14159265359) / 180);

	// Calculate target vector
	target = mp - cp;

	// Calculate angle between vectors
	angle = atan2f(forward.x * target.y - forward.y * target.x, forward.x * target.x + forward.y * target.y);

	// Convert radians to degrees
	angle = (angle * 180) / 3.14159265359;

	// Subtract calculated angle from forward angle
	angleDifference = ((r * 3.14159265359) / 180) - angle;

	if (angleDifference > 0.05f)
	{
		if (newRotation + (turnSpeed * dt) <= 360)
		{
			newRotation += turnSpeed * dt;
		}
		else
		{
			newRotation = (turnSpeed * dt) - (360 - newRotation);
		}
	}
	else if (angleDifference < -0.05f)
	{
		if (newRotation - (turnSpeed * dt) >= 0)
		{
			newRotation -= (turnSpeed * dt);
		}
		else
		{
			newRotation = 360 + (newRotation - (turnSpeed * dt));
		}
	}

	return newRotation;
}

void Player::destroyed()
{
	
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
