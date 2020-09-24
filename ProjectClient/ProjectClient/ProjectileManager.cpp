#include "ProjectileManager.h"

ProjectileManager::ProjectileManager()
{
	cannonballTexture.loadFromFile("gfx/cannonball.png");

	testRotation = 0;
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::Update(float dt)
{
	// Sort projectile lists and ensure removal of inactive
	std::vector<Cannonball> temp;

	for (auto &eProj : enemyProjectiles)
	{
		if (eProj.GetActive())
		{
			temp.push_back(eProj);
		}
	}
	enemyProjectiles = temp;
	temp.clear();

	for (auto &oProj : ownProjectiles)
	{
		if (oProj.GetActive())
		{
			temp.push_back(oProj);
		}
	}
	ownProjectiles = temp;
	temp.clear();

	// Update cannonballs
	for (auto &eProj : enemyProjectiles)
	{
		eProj.update(dt);
	}

	for (auto &oProj : ownProjectiles)
	{
		oProj.update(dt);
	}

	if (!ownProjectiles.empty())
	{
		testRotation = ownProjectiles[0].getRotation();
	}
}

void ProjectileManager::AddEnemyProjectile(sf::Vector2f pos, float speed, float angle, float range)
{
	// Simply store the new cannonball and its data in the list
	enemyProjectiles.push_back(Cannonball());
	enemyProjectiles[enemyProjectiles.size() - 1].SetActive(true);
	enemyProjectiles[enemyProjectiles.size() - 1].setPosition(pos);
	enemyProjectiles[enemyProjectiles.size() - 1].setOrigin(sf::Vector2f(8, 8));
	enemyProjectiles[enemyProjectiles.size() - 1].setOrigin(4, 4);
	enemyProjectiles[enemyProjectiles.size() - 1].setRotation(angle);
	enemyProjectiles[enemyProjectiles.size() - 1].setTexture(&cannonballTexture);
}

void ProjectileManager::AddOwnProjectile(sf::Vector2f pos, float speed, float angle, float range)
{
	// Simply store the new cannonball and its data in the list
	ownProjectiles.push_back(Cannonball());
	ownProjectiles[ownProjectiles.size() - 1].SetActive(true);
	ownProjectiles[ownProjectiles.size() - 1].setPosition(pos);
	ownProjectiles[ownProjectiles.size() - 1].setSize(sf::Vector2f(8, 8));
	ownProjectiles[ownProjectiles.size() - 1].setOrigin(4, 4);
	ownProjectiles[ownProjectiles.size() - 1].setRotation(angle);
	ownProjectiles[ownProjectiles.size() - 1].SetRange(range);
	ownProjectiles[ownProjectiles.size() - 1].SetSpeed(speed);
	ownProjectiles[ownProjectiles.size() - 1].setTexture(&cannonballTexture);
}

void ProjectileManager::Render(sf::RenderWindow * window)
{
	for (auto &enemy : enemyProjectiles)
	{
		window->draw(enemy);
	}

	for (auto &own : ownProjectiles)
	{
		window->draw(own);
	}
}


