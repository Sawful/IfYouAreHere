#pragma once
#include "Enemy.h"
#include "BulletSpawner.h"
#include "BulletSpawnerCircle1.h"

class BigCircleGuy : public Enemy
{
	BulletSpawner* mBulletSpawnerPTR;
	bool mAttacking;
	float mAttackAnimationTime;

public:
	BigCircleGuy(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture, std::vector<Path*> movementPath);

	virtual void Update(float deltaTime);
	virtual void Attack();
};

