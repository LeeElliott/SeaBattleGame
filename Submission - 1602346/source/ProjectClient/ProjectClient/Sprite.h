#ifndef SPRITE_H
#define SPRITE_H


#include <SFML\Graphics.hpp>

class Sprite : public sf::RectangleShape
{
public:
public:
	Sprite(const sf::Vector2f & size = sf::Vector2f(0, 0));
	~Sprite();
	virtual void update(float dt) = 0;
	void setVelocity(sf::Vector2f vel);
	void setVelocity(float vx, float vy);
	void setAlive(bool b);
	bool isAlive();
	void setVisible(bool b);
	bool isVisible();

	sf::Vector2f getVelocity();
	sf::FloatRect getAABB();
	virtual void updateAABB();
	virtual void collisionResponse();

protected:
	sf::Vector2f velocity;
	sf::FloatRect AABB;
	bool alive;
	bool visible;
};

#endif // !SPRITE_H
