#include "Input.h"

void Input::setKeyDown(int key)
{
	keys[key] = true;
}

void Input::setKeyUp(int key)
{
	keys[key] = false;
}

bool Input::isKeyDown(int key)
{
	return keys[key];
}

void Input::setMouseX(int lx)
{
	mouse.x = lx;
}

void Input::setMouseY(int ly)
{
	mouse.y = ly;
}

void Input::setMouseXY(int lx, int ly)
{
	mouse.x = lx;
	mouse.y = ly;
}

int Input::getMouseX()
{
	return mouse.x;
}

int Input::getMouseY()
{
	return mouse.y;
}

void Input::setMouseLeftDown(bool b)
{
	mouse.left = b;
}

bool Input::isLeftDown()
{
	return mouse.left;
}

void Input::setMouseRightDown(bool b)
{
	mouse.right = b;
}

bool Input::isRightDown()
{
	return mouse.right;
}