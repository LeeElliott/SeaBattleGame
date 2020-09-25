#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	enemyTex.loadFromFile("gfx/enemyship.png");

	enemies.push_back(Enemy());
	enemies[currentEnemies].setActive(true);
	enemies[currentEnemies].setPosition(400, 400);
	enemies[currentEnemies].setMyPosition(sf::Vector2f(400, 400));
	enemies[currentEnemies].setOrigin(sf::Vector2f(32, 32));
	enemies[currentEnemies].setID(3);
	enemies[currentEnemies].setRotation(0);
	enemies[currentEnemies].setSize(sf::Vector2f(64, 64));
	enemies[currentEnemies].setTexture(&enemyTex);
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::update(float dt)
{
	for (auto &Enemy : enemies)
	{
		sf::Vector2f newPos;

		if (Enemy.getPosition() != Enemy.getMyPosition())
		{
			newPos = Enemy.lerp(Enemy.getPosition(), Enemy.getMyPosition());
			Enemy.setPosition(newPos);
		}

		if (Enemy.getRotation() != Enemy.getMyRotation())
		{
			Enemy.setRotation(Enemy.rlerp(Enemy.getMyRotation(), atan2(newPos.x, newPos.y)));
		}
	}
}

float EnemyManager::ProximityLeft(sf::Vector2f pPos, float range, float pRot)
{
	float closest = 999;
	float angle = 999;

	for (auto &enemy : enemies)
	{
		// Calculate distance between player and enemy
		float distance = sqrtf(powf(enemy.getPosition().x - pPos.x, 2) + powf(enemy.getPosition().y - pPos.y, 2));

		if (distance <= range)
		{
			// Calculate angle
			float vectorAngle = atan2f((enemy.getPosition().x - pPos.x), (enemy.getPosition().y - pPos.y));
			vectorAngle *= 180 / 3.14159265359;
			if (vectorAngle < 0)
			{
				vectorAngle = 360 + vectorAngle;
			}

			float playerRotation = pRot;

			if (playerRotation < 90)
			{
				playerRotation += 360;
			}

			// Calculate difference
			float tempAngle = playerRotation - vectorAngle;

			if (tempAngle < 135 && tempAngle > 45)
			{
				if (distance < closest)
				{
					closest = distance;
					angle = tempAngle;
				}
			}
		}
	}

	return angle;
}

float EnemyManager::ProximityRight(sf::Vector2f pPos, float range, float pRot)
{
	float closest = 999;
	float angle = 999;

	for (auto &enemy : enemies)
	{
		// Calculate distance between player and enemy
		float distance = sqrtf(powf(enemy.getPosition().x - pPos.x, 2) + powf(enemy.getPosition().y - pPos.y, 2));

		if (distance <= range)
		{
			// Calculate angle
			float vectorAngle = atan2f((enemy.getPosition().x - pPos.x), (enemy.getPosition().y - pPos.y));
			vectorAngle *= 180 / 3.14159265359;
			if (vectorAngle < 0)
			{
				vectorAngle = 360 + vectorAngle;
			}

			float playerRotation = pRot;

			if (playerRotation < 90)
			{
				playerRotation += 360;
			}

			// Calculate difference
			float tempAngle = playerRotation - vectorAngle;

			if (tempAngle < 315 && tempAngle > 225)
			{
				if (distance < closest)
				{
					closest = distance;
					angle = tempAngle;
				}
			}
		}
	}

	return angle;
}

void EnemyManager::addEnemy(sf::Vector2f pos, sf::Vector2f origin, sf::Vector2f size, int id, float rot)
{
	// Simply store the new enemy and its data in the list
	enemies.push_back(Enemy());
	enemies[currentEnemies].setActive(true);
	enemies[currentEnemies].setPosition(pos);
	enemies[currentEnemies].setMyPosition(pos);
	enemies[currentEnemies].setOrigin(origin);
	enemies[currentEnemies].setID(id);
	enemies[currentEnemies].setRotation(rot);
	enemies[currentEnemies].setSize(size);
	enemies[currentEnemies].setTexture(&enemyTex);	
}

void EnemyManager::render(sf::RenderWindow* window)
{
	for (auto &enemy : enemies)
	{
		window->draw(enemy);
	}
}
