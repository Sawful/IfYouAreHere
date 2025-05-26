#pragma once
#include "BulletSpawner.h"

class Enemy;
class ExtraBoss;
class PlayerController;

class BulletSpawnerExtraBossPhase1Perma : public BulletSpawner
{
	float mRotation;

	Enemy* mOwner;

public:
	BulletSpawnerExtraBossPhase1Perma(Enemy* owner, Stage* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};

class BulletSpawnerExtraBoss1 : public BulletSpawner
{
	float mAttackTime = 4.0f;
	float mAttackCooldown = 2.0f;

	bool mIsAttacking;

	float mAttackDuration = 1.0f;
	float mAttackDurationTimer;

	int mAttackNumber;

	float mShotTime = 0.0f;
	float mShotCooldown = 0.125f;

	ExtraBoss* mOwner;

public:
	BulletSpawnerExtraBoss1(ExtraBoss* owner, Stage* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();
};

class BulletSpawnerExtraBoss2 : public BulletSpawner
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

	ExtraBoss* mOwner;

	sf::RenderWindow* mWindow;
	PlayerController* mPlayerController;

public:
	BulletSpawnerExtraBoss2(ExtraBoss* owner, Stage* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();

	virtual void EndAttack();
};

class BulletSpawnerExtraBoss3 : public BulletSpawner
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

	ExtraBoss* mOwner;

	sf::RenderWindow* mWindow;

public:
	BulletSpawnerExtraBoss3(ExtraBoss* owner, Stage* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();
};

class BulletSpawnerExtraBoss4 : public BulletSpawner
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

	ExtraBoss* mOwner;

	sf::RenderWindow* mWindow;

public:
	BulletSpawnerExtraBoss4(ExtraBoss* owner, Stage* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);

	virtual void Reset();
};

class BulletSpawnerExtraBoss5 : public BulletSpawner
{
	float mShotTime = 0.1f;
	float mShotCooldown = 0.1f;

	float mRotation;
	float mRotationAdd;

	bool mRotating = true;
	float mRotationCooldown = 10.0f;
	float mRotationTime = 10.0f;

	Enemy* mOwner;

public:
	BulletSpawnerExtraBoss5(Enemy* owner, Stage* currentStage);

	void SpawnBullet();

	virtual void Update(float dt);
};