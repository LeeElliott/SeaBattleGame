#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	enemyTex.loadFromFile("gfx/enemyship.png");

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

sf::Vector2f EnemyManager::checkPositions(sf::Vector2f playerPos, float rotation)
{
	for (size_t i = 0; i < 20; i++)
	{
		// Calculate vector line between player and enemy
		sf::Vector2f enemyPos = enemies[i].getPosition();
		sf::Vector2f playerToEnemy = sf::Vector2f(playerPos.x - enemyPos.x, playerPos.y - enemyPos.y);

		// Calculate the angle of this vector from 0
		float angleToEnemy = atan(playerToEnemy.y / playerToEnemy.x);
		angleToEnemy = (float)(180 / 3.14159265) * angleToEnemy;

		// Compare to player rotation +90
		if (angleToEnemy - rotation > 75.0f && angleToEnemy - rotation < 105.0f)
		{
			return sf::Vector2f(sqrt(playerToEnemy.x), sqrt(playerToEnemy.y));
		}		
	}

	return sf::Vector2f(0.0f, 0.0f);
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
