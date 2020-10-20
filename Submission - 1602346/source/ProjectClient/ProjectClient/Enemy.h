#ifndef ENEMY_H
#define ENEMY_H

#include "Sprite.h"
#include "Input.h"

class Enemy : public Sprite
{
public:
	Enemy();
	~Enemy();

	void update(float dt);
	void updateStatus(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f orig, float rot);

	void setID(int id) { identifier = id; }
	void setOrigin(sf::Vector2f orig) { origin = orig; }
	void setFacing(sf::Vector2f face) { facing = face; }
	void setActive(bool a) { active = a; }
	void setMyPosition(sf::Vector2f pos) { myPosition = pos; }

	sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b);
	float rlerp(float ra, float rb);

	int getID() { return identifier; }
	sf::Vector2f getOrigin() { return origin; }
	sf::Vector2f getFacing() { return facing; }
	bool getActive() { return active; }
	sf::Vector2f getMyPosition() { return myPosition; }
	float getMyRotation() { return myRotation; }

protected:
	sf::Vector2f facing;
	sf::Vector2f myPosition;
	float myRotation;
	sf::Vector2f origin;
	int identifier;
	bool active;
};

#endif // !ENEMY_H
