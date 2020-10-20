#include "Item.h"

Item::Item()
{
	setActive(false);
}


Item::~Item()
{
}

void Item::update(float dt)
{
	updateAABB();
}
