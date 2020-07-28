#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include "Enemy.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void update(float dt);

	sf::Vector2f checkPositions(sf::Vector2f playerPos, float rotation);
	void addEnemy(sf::Vector2f pos, sf::Vector2f origin, sf::Vector2f size, int id, float rot);
	void render(sf::RenderWindow* window);
	
	std::vector<Enemy> enemies;

protected:	
	sf::Texture enemyTex;
	int currentEnemies = 0;
};

#endif // !ENEMY_MANAGER_H
