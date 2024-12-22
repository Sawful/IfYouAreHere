#pragma once
#include "BulletSpawner.h"

class BulletSpawnerBoss11Main : public BulletSpawner
{
	float mShotTime = 1.0f;
	float mShotCooldown = 1.0f;

	float mMainAttackCooldown = 8.0f;
	float mMainAttackTime = 0.0f;

	int mShotsFired;

	sf::Texture mBulletTexture;

	Enemy* mOwner;
	PlayerController* mPlayerController;

public:
	BulletSpawnerBoss11Main(Enemy* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};

class BulletSpawnerBoss11Sub : public BulletSpawner
{
	float mShotTime = 0.0f;
	float mShotCooldown = 0.01f;

	float mSubAttackCooldown = 8.0f;
	float mSubAttackTime = 4.0f;

	float mSubAttackDuration = 3.0f;
	bool mAttacking;

	sf::Texture mBulletTexture;
	Enemy* mOwner;

public:
	BulletSpawnerBoss11Sub(Enemy* owner);

	void SpawnBullet();

	virtual void Update(float dt);
};

class BulletSpawnerBoss12 : public BulletSpawner
{
	float mFullAttackCooldown = 15.0f;
	float mFullAttackTime = 0.0f;

	float mWaitCooldown = 3.0f;
	float mWaitTime = 0.0f;

	float mShotTime = 0.05f;
	float mShotCooldown = 0.05f;

	bool mAttacking1;
	bool mAttacking2;
	
	sf::Texture mBulletTexture;

	Enemy* mOwner;
	PlayerController* mPlayerController;

public:
	BulletSpawnerBoss12(Enemy* owner, Level* currentStage);

	void SpawnBullet();

	void RedirectBullets();

	virtual void Update(float dt);
};

class BulletSpawnerBoss13 : public BulletSpawner
{
	float mShotTime = 0.5f;
	float mShotCooldown = 0.5f;

	bool mSpreading;
	float mSpreadCooldown = 15.0f;
	float mSpreadTime = 15.0f;
	float mSpread;

	sf::Texture mBulletTexture;

	Enemy* mOwner;
	PlayerController* mPlayerController;

public:
	BulletSpawnerBoss13(Enemy* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};

class BulletSpawnerBoss14 : public BulletSpawner
{
	float mShotTime = 1.0f;
	float mShotCooldown = 1.0f;

	float mAcceleration;

	bool mTurningRight;

	bool mAccelerating;
	float mAccelerationCooldown = 20.0f;
	float mAccelerationTime = 20.0f;

	sf::Texture mBulletTexture;

	Enemy* mOwner;

public:
	BulletSpawnerBoss14(Enemy* owner);

	void SpawnBullet();

	virtual void Update(float dt);
};