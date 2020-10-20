#include "Enemy.h"

Enemy::Enemy()
{
	active = true;
}

Enemy::~Enemy()
{

}

void Enemy::update(float dt)
{
	
}

void Enemy::updateStatus(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f orig, float rot)
{
	myPosition = pos;
	myRotation = rot;
	
	setSize(size);
	setOrigin(orig);
}

sf::Vector2f Enemy::lerp(sf::Vector2f a, sf::Vector2f b)
{
	sf::Vector2f factor = 0.01f * (b - a);

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

float Enemy::rlerp(float ra, float rb)
{
	// Reduce rotation amount by a factor
	float factor = 0.01f * (rb - ra);

	float rotation = ra + factor;
	rotation;

	return rotation;
}


