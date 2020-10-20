#include "Cursor.h"

Cursor::Cursor()
{

}

Cursor::~Cursor()
{

}

void Cursor::update(float dt)
{
	position.x = (screenCentre.x - 336) + input->getMouseX();
	position.y = (screenCentre.y - 192) + input->getMouseY();

	setPosition(position.x, position.y);
}

void Cursor::passInput(Input* in)
{
	input = in;
}
