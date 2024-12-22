#pragma once
#include "BulletSpawner.h"


class BulletSpawnerSlug1 : public BulletSpawner
{
	float mShotTime = 1.5f;
	float mShotCooldown = 0.5f;

	sf::Texture mBulletTexture;

	Enemy* mOwner;

	PlayerController* mPlayerController;

public:
	BulletSpawnerSlug1(Enemy* owner, Level* currentStage);

	void SpawnBullet(sf::Vector2f targetPosition);

	virtual void Update(float dt);
};

