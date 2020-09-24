#ifndef PROJECTILE_MANAGER_H
#define PROJECTILE_MANAGER_H

#include "Cannonball.h"

class ProjectileManager
{
public:
	ProjectileManager();
	~ProjectileManager();

	void Update(float dt);
	void AddEnemyProjectile(sf::Vector2f pos, float speed, float angle, float range);
	void AddOwnProjectile(sf::Vector2f pos, float speed, float angle, float range);
	void Render(sf::RenderWindow* window);

	std::vector<Cannonball> enemyProjectiles;
	std::vector<Cannonball> ownProjectiles;
	float getCR() { return testRotation; }
protected:
	// Texture
	sf::Texture cannonballTexture;

	// DEBUG
	float testRotation;
};

#endif // !PROJECTILE_MANAGER_H
