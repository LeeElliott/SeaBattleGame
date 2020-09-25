#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include <string.h>
#include "Sprite.h"
#include "Input.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"

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
	void setProjectileMan(ProjectileManager* pM) { pManager = pM; }
	void setShotTexture(sf::Texture* sT) { shotTex = sT; }

	// Getters for stat variables
	int getUserID() { return userID; }
	std::string getUsername(){ return username; }
	sf::Vector2f getHome() { return home; }
	float getHealthPoints() { return healthPoints; }
	float getMoveSpeed() { return moveSpeed; }
	float getTurnSpeed() { return turnSpeed; }
	int getNumCannon() { return numCannon; }
	float getRange() { return range; }
	float getFireSpread() { return fireSpread; }
	float getDamage() { return damage; }
	float getFireRate() { return fireRate; }

	// Setters for stat variables
	void setUserID(int ID) { userID = ID; }
	void setUsername(std::string name) { username = name; }
	void setHome(sf::Vector2f h) { home = h; }
	void setHealthPoints(float hp) { healthPoints = hp; }
	void setMoveSpeed(float mSpeed) { moveSpeed = mSpeed; }
	void setTurnSpeed(float tSpeed) { turnSpeed = tSpeed; }
	void setNumCannon(int nCannon) { numCannon = nCannon; }
	void setRange(float r) { range = r; }
	void setFireSpread(float spread) { fireSpread = spread; }
	void setDamage(float dam) { damage = dam; }
	void setFireRate(float rate) { fireRate = rate; }

	/* DEBUG */
	float getAngle() { return angleDifference; }
	sf::Vector2f getForward() { return forward; }

protected:
	void destroyed();
	void checkCollision();
	bool enemyCollision(int i);

	// Movement and rotation
	sf::Vector2f PositionLerp(float dt);
	float RotationLerp(sf::Vector2f a, sf::Vector2f b, float r, float dt);
	
	// Fire!!
	void Fire(float angle);

	Input* input;
	sf::RenderWindow* window;
	EnemyManager* eManager;
	ProjectileManager* pManager;

	sf::Vector2f position, screenCentre;

	float leftDelay;
	float rightDelay;

	// Stat variables to be loaded from database
	int userID;
	std::string username;
	sf::Vector2f home;
	float healthPoints;
	float moveSpeed;
	float turnSpeed;
	int numCannon;
	float range;
	float fireSpread;
	float damage;
	float fireRate;

	sf::Texture* shotTex;

	/* DEBUG */
	float angle;
	float angleDifference;
	sf::Vector2f forward;
};

#endif // PLAYER_H
