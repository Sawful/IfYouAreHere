#pragma once
#include "BulletSpawner.h"

class Enemy;
class Boss2;
class PlayerController;

class BulletSpawnerBoss2Phase1Perma : public BulletSpawner
{
	float mRotation;

	sf::Texture mBulletTexture;

	Enemy* mOwner;

public:
	BulletSpawnerBoss2Phase1Perma(Enemy* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};

class BulletSpawnerBoss21 : public BulletSpawner
{
	float mAttackTime = 4.0f;
	float mAttackCooldown = 2.0f;

	bool mIsAttacking;

	float mAttackDuration = 1.0f;
	float mAttackDurationTimer;

	int mAttackNumber;

	float mShotTime = 0.0f;
	float mShotCooldown = 0.125f;

	sf::Texture mBulletTexture;

	Boss2* mOwner;

public:
	BulletSpawnerBoss21(Boss2* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();
};

class BulletSpawnerBoss22 : public BulletSpawner
{
	float mAttackTime = 1.0f;
	float mAttackCooldown = 1.0f;

	bool mIsPreview;

	float mPreviewTime = 2.0f;
	float mPreviewCooldown = 2.0f;

	bool mIsAttacking;

	sf::Vector2f mDirection;

	float mAttackDuration = 2.0f;
	float mAttackDurationTimer;

	bool mHasAttacked;

	sf::Texture mBulletTexture;

	Boss2* mOwner;

	sf::RenderWindow* mWindow;
	PlayerController* mPlayerController;

public:
	BulletSpawnerBoss22(Boss2* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();

	virtual void EndAttack();
};

class BulletSpawnerBoss23 : public BulletSpawner
{
	float mAttackTime = 1.0f;
	float mAttackCooldown = 1.0f;

	bool mIsPreview;

	float mPreviewTime = 1.5f;
	float mPreviewCooldown = 1.5f;

	bool mIsAttacking;

	float mAttackDuration = 2.0f;
	float mAttackDurationTimer;

	bool mHasAttacked;

	sf::Texture mBulletTexture;

	Boss2* mOwner;

	sf::RenderWindow* mWindow;

public:
	BulletSpawnerBoss23(Boss2* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();
};

class BulletSpawnerBoss24 : public BulletSpawner
{
	float mAttackTime = 1.0f;
	float mAttackCooldown = 1.0f;

	bool mIsPreview;

	float mPreviewTime = 1.5f;
	float mPreviewCooldown = 1.5f;

	bool mIsAttacking;

	float mAttackDuration = 2.0f;
	float mAttackDurationTimer;

	bool mHasAttacked;

	sf::Texture mBulletTexture;

	Boss2* mOwner;

	sf::RenderWindow* mWindow;

public:
	BulletSpawnerBoss24(Boss2* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();
};

class BulletSpawnerBoss25 : public BulletSpawner
{
	float mShotTime = 0.1f;
	float mShotCooldown = 0.1f;

	float mRotation;
	float mRotationAdd;

	bool mRotating = true;
	float mRotationCooldown = 10.0f;
	float mRotationTime = 10.0f;

	sf::Texture mBulletTexture;

	Enemy* mOwner;

public:
	BulletSpawnerBoss25(Enemy* owner, Level* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};