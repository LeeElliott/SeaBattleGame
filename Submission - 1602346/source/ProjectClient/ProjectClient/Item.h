#ifndef ITEM_H
#define ITEM_H

#include "Sprite.h"
#include "Input.h"

class Item : public Sprite
{
public:
	Item();
	~Item();

	void update(float dt);

	void setOrigin(sf::Vector2f orig) { origin = orig; }
	void setActive(bool a) { active = a; }

	sf::Vector2f getOrigin() { return origin; }
	bool getActive() { return active; }

protected:
	sf::Vector2f position;
	sf::Vector2f origin;
	bool active;
};

#endif // ITEM_H
