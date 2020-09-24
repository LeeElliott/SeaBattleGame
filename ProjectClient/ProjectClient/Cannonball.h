#pragma once

#include "Sprite.h"

class Cannonball : public Sprite
{
public:
	Cannonball();
	~Cannonball();

	void update(float dt);

	// Getters
	bool GetActive() { return active; }

	// Setters
	void SetSpeed(float s) { moveSpeed = s; }
	void SetRange(float r) { range = r; }
	void SetActive(bool a) { active = a; }

protected:
	float moveSpeed;
	float range;
	float moveDistance;
	bool active;
};

