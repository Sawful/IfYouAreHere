#pragma once
#include "BulletSpawner.h"


class BulletSpawnerSlug1 : public BulletSpawner
{
	float mShotTime = 1.5f;
	float mShotCooldown = 0.5f;

	Enemy* mOwner;

	PlayerController* mPlayerController;

public:
	BulletSpawnerSlug1(Enemy* owner, Stage* currentStage);

	void SpawnBullet(sf::Vector2f targetPosition);

	virtual void Update(float dt);
};

