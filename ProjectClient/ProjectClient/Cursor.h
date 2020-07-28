#ifndef CURSOR_H
#define CURSOR_H

#include "Sprite.h"
#include "Input.h"

class Cursor : public Sprite
{
public:
	Cursor();
	~Cursor();

	void update(float dt);
	void passInput(Input* in);
	void setCentre(sf::Vector2f c) { screenCentre = c; }

protected:
	Input* input;
	sf::Vector2f position, screenCentre;
};

#endif // !CURSOR_H
