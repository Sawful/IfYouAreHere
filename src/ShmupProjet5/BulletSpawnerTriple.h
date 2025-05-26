#pragma once
#include "BulletSpawner.h"

class PlayerController;

class BulletSpawnerTriple : public BulletSpawner
{
	float mShotTime = 1.0f;
	float mShotCooldown = 2.0f;

	Enemy* mOwner;
	PlayerController* mPlayerController;

public:
	BulletSpawnerTriple(Enemy* owner, Stage* currentStage);

	void SpawnBullet(sf::Vector2f targetPosition);

	virtual void Update(float dt);
};

