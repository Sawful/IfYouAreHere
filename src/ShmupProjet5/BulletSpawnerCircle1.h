#pragma once
#include "BulletSpawner.h"
class BulletSpawnerCircle1 : public BulletSpawner
{
	float mShotTime = 1.5f;
	float mShotCooldown = 2.0f;

	sf::Texture mBulletTexture;

	Enemy* mOwner;

public:
	BulletSpawnerCircle1(Enemy* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};

