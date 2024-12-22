#pragma once
#include "Enemy.h"
#include "BulletSpawnerTriple.h"

class TripleShotCritter : public Enemy
{
	BulletSpawner* mBulletSpawnerPTR;
	/*bool mAttacking;
	float mAttackAnimationTime;*/

public:
	TripleShotCritter(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture, std::vector<Path*> movementPath);

	virtual void Update(float deltaTime);
	virtual void Attack();
};

