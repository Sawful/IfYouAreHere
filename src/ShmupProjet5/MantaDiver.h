#pragma once
#include "Enemy.h"
#include "Path.h"

class BulletSpawner;

class MantaDiver : public Enemy
{
	BulletSpawner* mBulletSpawnerPTR;

public:
	MantaDiver(sf::Vector2f position, float rotation, bool isActive, TextureName texture, std::vector<Path*> movementPath);

	virtual void Update(float deltaTime);
	virtual void Attack();
	virtual void Move(float deltaTime) override;
};

