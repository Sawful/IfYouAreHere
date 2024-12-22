#pragma once
#include "BulletSpawner.h"

class PlayerController;

class BulletSpawnerTriple : public BulletSpawner
{
	float mShotTime = 1.0f;
	float mShotCooldown = 2.0f;

	sf::Texture mBulletTexture;

	Enemy* mOwner;
	PlayerController* mPlayerController;

public:
	BulletSpawnerTriple(Enemy* owner, Level* currentStage);

	void SpawnBullet(sf::Vector2f targetPosition);

	virtual void Update(float dt);
};

