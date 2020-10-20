#ifndef ITEM_MANAGER_H
#define ITEM_MANAGER_H

#include "Item.h"

class ItemManager
{
public:
	ItemManager();
	~ItemManager();
	
	void update(float dt);
	void addItem();
	void updateItems(float dt);
	void respawn();
	void render(sf::RenderWindow * window);

	std::vector<Item> items;

protected:
	sf::Texture itemTex;
	float respawnTimer = 15.0f;
};

#endif // ITEM_MANAGER_H
