#include "BulletSpawnerBoss2.h"
#include "BulletBase.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "Boss2.h"
#include <math.h>
#include <numbers>

BulletSpawnerBoss21::BulletSpawnerBoss21(Boss2* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mAttackNumber = 0;

	mIsAttacking = false;
}

void BulletSpawnerBoss21::SpawnBullet()
{
	if (mAttackDurationTimer < 0.5f)
	{
		mAttackDurationTimer = mAttackDurationTimer;
	}

	for (int i = 0; i < 24; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 250.0f, sf::Vector2f(cos(i * std::numbers::pi / 12), sin(i * std::numbers::pi / 12)), mOwner->getPosition(), getRotation(), BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}
}

void BulletSpawnerBoss21::Update(float dt)
{
	mShotTime -= dt;
	mAttackTime -= dt;
	mAttackDurationTimer -= dt;

	setPosition(mOwner->getPosition());
	if(mIsAttacking)
	{
		if (mShotTime <= 0)
		{
			SpawnBullet();
			mShotTime = mShotCooldown;
		}

		if (mAttackDurationTimer <= 0)
		{
			mIsAttacking = false;
		}
	}

	if (mAttackNumber >= 3)
	{
		return;
	}

	if (mAttackTime <= 0 && !mIsAttacking)
	{
		mAttackNumber++;
		mIsAttacking = true;
		mAttackDurationTimer = mAttackDuration;
		mAttackTime = mAttackCooldown;
	}
}

void BulletSpawnerBoss21::Reset()
{
	mAttackNumber = -1;
	mIsAttacking = false;
	mAttackTime = mAttackCooldown;
}

BulletSpawnerBoss22::BulletSpawnerBoss22(Boss2* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mWindow = GameManager::GetInstance()->GetWindow();
	mPlayerController = currentStage->GetPlayerController();

	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;
}

void BulletSpawnerBoss22::SpawnBullet()
{
	GameManager::GetInstance()->GetSceneManager()->ShakeStage2(1.5f);

	for (int i = 0; i < 24; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 0, sf::Vector2f(0, 1), mOwner->getPosition() + (float)(i + 2.5f) * mDirection * 50.0f, 0, BULLET_TEXTURE, ENEMYBULLET, true, 150.0f);
		newBullet->SetTransparency(0);
		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerBoss22::Update(float dt)
{
	mAttackTime -= dt;
	mPreviewTime -= dt;
	mAttackDurationTimer -= dt;

	if (mIsAttacking)
	{
		// Attacks first time
		if (!mHasAttacked)
		{
			mOwner->DisplayLaser(true);
			SpawnBullet();
			mHasAttacked = true;
		}

		// Attack ends
		if (mAttackDurationTimer <= 0.0f)
		{
			EndAttack();
			mIsAttacking = false;
		}
	}

	if (mHasAttacked)
	{
		return;
	}

	// Preview end
	else if (mIsPreview && mPreviewTime <= 0.0f)
	{
		mAttackDurationTimer = mAttackDuration;
		mIsAttacking = true;
		mIsPreview = false;

		mOwner->SetPreviewRectangle(false);
	}

	// Preview start
	else if (mAttackTime <= 0.0f && !mIsPreview)
	{
		mDirection = mPlayerController->GetActivePlayerPosition() - mOwner->getPosition();

		mDirection = *NormalizeV2f(mDirection);

		float rotation = atan2(mDirection.y, mDirection.x);
		rotation = rotation * 180 / std::numbers::pi;

		mOwner->DisplayLaser(false, mOwner->getPosition(), rotation);
		mOwner->SetPreviewRectangle(true, mOwner->getPosition(), rotation);

		mPreviewTime = mPreviewCooldown;
		mIsPreview = true;
	}
}

void BulletSpawnerBoss22::Reset()
{
	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;

	mAttackTime = mAttackCooldown;

	mOwner->DisplayLaser(false);
	mOwner->SetPreviewRectangle(false);

	RemoveBullets();
}

void BulletSpawnerBoss22::EndAttack()
{
	Reset();
}

BulletSpawnerBoss23::BulletSpawnerBoss23(Boss2* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mWindow = GameManager::GetInstance()->GetWindow();

	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;
}

void BulletSpawnerBoss23::SpawnBullet()
{
	GameManager::GetInstance()->GetSceneManager()->ShakeStage2(1.5f);
	for (int i = 0; i < 24; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 0, sf::Vector2f(0, 1), sf::Vector2f(-200.0f + i * 50.0f, 800.0f), 0, BULLET_TEXTURE, ENEMYBULLET, true, 150.0f);
		newBullet->SetTransparency(0);
		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerBoss23::Update(float dt)
{
	mAttackTime -= dt;
	mPreviewTime -= dt;
	mAttackDurationTimer -= dt;

	if (mIsAttacking)
	{
		// Attacks first time
		if (!mHasAttacked)
		{
			mOwner->DisplayLaser(true, sf::Vector2f(0.0f, 650.0f), 0);
			SpawnBullet();
			mHasAttacked = true;
		}

		// Attack ends
		if (mAttackDurationTimer <= 0.0f)
		{
			mOwner->DisplayLaser(false);
			Reset();
			mIsAttacking = false;
		}
	}

	if (mHasAttacked)
	{
		return;
	}

	// Preview end
	else if (mIsPreview && mPreviewTime <= 0.0f)
	{
		mAttackDurationTimer = mAttackDuration;
		mIsAttacking = true;
		mIsPreview = false;
		mOwner->SetPreviewRectangle(false);
	}

	// Preview start
	else if (mAttackTime <= 0.0f && !mIsPreview)
	{
		mPreviewTime = mPreviewCooldown;
		mIsPreview = true;
		mOwner->SetPreviewRectangle(true, sf::Vector2f(10.0f, 640.0f), 0);
	}
}

void BulletSpawnerBoss23::Reset()
{
	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;

	RemoveBullets();
	mOwner->SetPreviewRectangle(false);
	mOwner->DisplayLaser(false);
	mAttackTime = mAttackCooldown;
}

BulletSpawnerBoss24::BulletSpawnerBoss24(Boss2* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mWindow = GameManager::GetInstance()->GetWindow();

	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;
}

void BulletSpawnerBoss24::SpawnBullet()
{
	GameManager::GetInstance()->GetSceneManager()->ShakeStage2(1.5f);

	for (int i = 0; i < 24; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 0, sf::Vector2f(0, 1), sf::Vector2f(-200.0f + i * 50.0f, 300.0f), 0, BULLET_TEXTURE, ENEMYBULLET, true, 150.0f);
		newBullet->SetTransparency(0);
		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerBoss24::Update(float dt)
{
	mAttackTime -= dt;
	mPreviewTime -= dt;
	mAttackDurationTimer -= dt;

	if (mIsAttacking)
	{
		// Attacks first time
		if (!mHasAttacked)
		{
			mOwner->DisplayLaser(true, sf::Vector2f(0.0f, 150.0f), 0);
			SpawnBullet();
			mHasAttacked = true;
		}

		// Attack ends
		if (mAttackDurationTimer <= 0.0f)
		{
			mOwner->DisplayLaser(false);
			Reset();
			mIsAttacking = false;
		}
	}

	if (mHasAttacked)
	{
		return;
	}

	// Preview end
	else if (mIsPreview && mPreviewTime <= 0.0f)
	{
		mAttackDurationTimer = mAttackDuration;
		mIsAttacking = true;
		mIsPreview = false;

		mOwner->SetPreviewRectangle(false);
	}

	// Preview start
	else if (mAttackTime <= 0.0f && !mIsPreview)
	{
		mPreviewTime = mPreviewCooldown;
		mIsPreview = true;
		mOwner->SetPreviewRectangle(true, sf::Vector2f(10.0f, 160.0f), 0);
	}
}

void BulletSpawnerBoss24::Reset()
{
	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;

	RemoveBullets();
	mOwner->SetPreviewRectangle(false);
	mOwner->DisplayLaser(false);
	mAttackTime = mAttackCooldown;
}


BulletSpawnerBoss2Phase1Perma::BulletSpawnerBoss2Phase1Perma(Enemy* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mRotation = 0;
}

void BulletSpawnerBoss2Phase1Perma::SpawnBullet()
{
	sf::Vector2f position = mOwner->getPosition();
	mRotation += std::numbers::pi / 16;
	for (int i = 0; i < 8; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 200.0f, sf::Vector2f(cos(i * std::numbers::pi / 4 + mRotation), sin(i * std::numbers::pi / 4 + mRotation)), position, 0, BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}
}

void BulletSpawnerBoss2Phase1Perma::Update(float dt)
{
}

BulletSpawnerBoss25::BulletSpawnerBoss25(Enemy* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mRotation = 0;
}

void BulletSpawnerBoss25::SpawnBullet()
{
	sf::Vector2f position = mOwner->getPosition();

	for (int i = 0; i < 8; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 300.0f, sf::Vector2f(cos(i * std::numbers::pi / 4 + mRotation), sin(i * std::numbers::pi / 4 + mRotation)), position, 0, BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}
}

void BulletSpawnerBoss25::Update(float dt)
{
	if (mRotating)
	{
		mRotationAdd = std::lerp(mRotationAdd, 1.6f * std::numbers::pi, 0.1f * dt);
	}

	else
	{
		mRotationAdd = std::lerp(mRotationAdd, 1.6f * -std::numbers::pi, 0.1f * dt);
	}

	mRotation += mRotationAdd * dt;
	
	if (mRotationTime <= 0)
	{
		mRotationTime = mRotationCooldown;
		mRotating = !mRotating;
	}

	mShotTime -= dt;

	if (mShotTime <= 0)
	{
		SpawnBullet();
		mShotTime = mShotCooldown;
	}
}
