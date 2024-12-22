#pragma once
#include "cmath"

#include "BulletSpawner.h"
#include "BulletBase.h"
#include "PlayerController.h"
#include "Scene.h"

class Enemy;

class BulletSpawnerTest: public BulletSpawner
{
	sf::Clock mShotCooldownClock;
	float mShotCooldown = 0.5f;

	sf::Texture mBulletTexture;

	Enemy* mOwner;

	PlayerController* mPlayerController;

public:
	BulletSpawnerTest(Enemy* owner);

	void SpawnBullet(sf::Vector2f targetPosition);

	virtual void Update(float dt);
};

