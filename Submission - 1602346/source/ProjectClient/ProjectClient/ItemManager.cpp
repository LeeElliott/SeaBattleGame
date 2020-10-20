#include "ItemManager.h"


ItemManager::ItemManager()
{
	itemTex.loadFromFile("gfx/crate.jpg");

	for (int i = 0; i < 20; i++)
	{
		addItem();
	}
}

ItemManager::~ItemManager()
{

}

void ItemManager::update(float dt)
{
	if (respawnTimer <= 0.0f)
	{
		respawn();
		respawnTimer = 15.0f;
	}
	else
	{
		respawnTimer -= dt;
	}

	updateItems(dt);
}

void ItemManager::addItem()
{
	Item temp;
	temp.setActive(true);
	temp.setPosition(static_cast <float> (rand() % 2048), static_cast <float> (rand() % 2048));
	temp.setSize(sf::Vector2f(20.0f, 20.0f));
	temp.setOrigin(sf::Vector2f(10.0f, 10.0f));
	temp.setTexture(&itemTex);

	items.push_back(temp);
}

void ItemManager::updateItems(float dt)
{
	for (auto &item : items)
	{
		if (item.getActive())
		{
			item.update(dt);
		}
	}
}

void ItemManager::respawn()
{
	for (auto &item : items)
	{
		if (!item.getActive())
		{
			item.setActive(true);
			break;
		}
	}
}

void ItemManager::render(sf::RenderWindow* window)
{
	for (auto &item : items)
	{
		if (item.getActive())
		{
			window->draw(item);
		}
	}
}