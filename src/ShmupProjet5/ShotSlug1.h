#pragma once
#include "Enemy.h"
#include "Path.h"

class BulletSpawner;

class ShotSlug1 : public Enemy
{
	BulletSpawner* mBulletSpawnerPTR;

public:
	ShotSlug1(sf::Vector2f position, float rotation, bool isActive, TextureName texture, std::vector<Path*> movementPath);

	virtual void Update(float deltaTime);
	virtual void Attack();
};

