#include "Cannonball.h"

Cannonball::Cannonball()
{
	moveDistance = 0;
}

Cannonball::~Cannonball()
{
}

void Cannonball::update(float dt)
{
	if (moveDistance < range)
	{
		sf::Vector2f currentPosition = getPosition();
		sf::Vector2f forward;

		// Calculate forward vector
		forward.x = cosf((getRotation() * 3.14159265359) / 180);
		forward.y = sinf((getRotation() * 3.14159265359) / 180);

		sf::Vector2f lerp = currentPosition + ((forward * moveSpeed) * dt);

		setPosition(lerp);

		moveDistance += sqrtf(pow(lerp.x - currentPosition.x, 2) + pow(lerp.y - currentPosition.y, 2));
	}
	else
	{
		SetActive(false);
	}
}
