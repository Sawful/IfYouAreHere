#include "BulletSpawnerExtraBoss.h"
#include "BulletBase.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "PlayerController.h"
#include "Enemy.h"
#include "ExtraBoss.h"
#include <math.h>
#include <numbers>

BulletSpawnerExtraBoss1::BulletSpawnerExtraBoss1(ExtraBoss* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mAttackNumber = 0;

	mIsAttacking = false;
}

void BulletSpawnerExtraBoss1::SpawnBullet()
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

void BulletSpawnerExtraBoss1::Update(float dt)
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

void BulletSpawnerExtraBoss1::Reset()
{
	mAttackNumber = -1;
	mIsAttacking = false;
	mAttackTime = mAttackCooldown;
}

BulletSpawnerExtraBoss2::BulletSpawnerExtraBoss2(ExtraBoss* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mWindow = GameManager::GetInstance()->GetWindow();
	mPlayerController = currentStage->GetPlayerController();

	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;
}

void BulletSpawnerExtraBoss2::SpawnBullet()
{
	GameManager::GetInstance()->GetSceneManager()->ShakeExtraStage(1.5f);

	for (int i = 0; i < 24; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 0, sf::Vector2f(0, 1), mOwner->getPosition() + (float)(i + 2.5f) * mDirection * 50.0f, 0, BULLET_TEXTURE, ENEMYBULLET, true, 150.0f);
		newBullet->SetTransparency(0);
		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerExtraBoss2::Update(float dt)
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

void BulletSpawnerExtraBoss2::Reset()
{
	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;

	mAttackTime = mAttackCooldown;

	mOwner->DisplayLaser(false);
	mOwner->SetPreviewRectangle(false);

	RemoveBullets();
}

void BulletSpawnerExtraBoss2::EndAttack()
{
	Reset();
}

BulletSpawnerExtraBoss3::BulletSpawnerExtraBoss3(ExtraBoss* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mWindow = GameManager::GetInstance()->GetWindow();

	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;
}

void BulletSpawnerExtraBoss3::SpawnBullet()
{
	GameManager::GetInstance()->GetSceneManager()->ShakeExtraStage(1.5f);
	for (int i = 0; i < 24; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 0, sf::Vector2f(0, 1), sf::Vector2f(-200.0f + i * 50.0f, 800.0f), 0, BULLET_TEXTURE, ENEMYBULLET, true, 150.0f);
		newBullet->SetTransparency(0);
		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerExtraBoss3::Update(float dt)
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

void BulletSpawnerExtraBoss3::Reset()
{
	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;

	RemoveBullets();
	mOwner->SetPreviewRectangle(false);
	mOwner->DisplayLaser(false);
	mAttackTime = mAttackCooldown;
}

BulletSpawnerExtraBoss4::BulletSpawnerExtraBoss4(ExtraBoss* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mWindow = GameManager::GetInstance()->GetWindow();

	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;
}

void BulletSpawnerExtraBoss4::SpawnBullet()
{
	GameManager::GetInstance()->GetSceneManager()->ShakeExtraStage(1.5f);

	for (int i = 0; i < 24; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 0, sf::Vector2f(0, 1), sf::Vector2f(-200.0f + i * 50.0f, 300.0f), 0, BULLET_TEXTURE, ENEMYBULLET, true, 150.0f);
		newBullet->SetTransparency(0);
		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerExtraBoss4::Update(float dt)
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

void BulletSpawnerExtraBoss4::Reset()
{
	mIsPreview = false;
	mIsAttacking = false;
	mHasAttacked = false;

	RemoveBullets();
	mOwner->SetPreviewRectangle(false);
	mOwner->DisplayLaser(false);
	mAttackTime = mAttackCooldown;
}


BulletSpawnerExtraBossPhase1Perma::BulletSpawnerExtraBossPhase1Perma(Enemy* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mRotation = 0;
}

void BulletSpawnerExtraBossPhase1Perma::SpawnBullet()
{
	sf::Vector2f position = mOwner->getPosition();
	mRotation += std::numbers::pi / 16;
	for (int i = 0; i < 8; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 200.0f, sf::Vector2f(cos(i * std::numbers::pi / 4 + mRotation), sin(i * std::numbers::pi / 4 + mRotation)), position, 0, BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}
}

void BulletSpawnerExtraBossPhase1Perma::Update(float dt)
{
}

BulletSpawnerExtraBoss5::BulletSpawnerExtraBoss5(Enemy* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mRotation = 0;
}

void BulletSpawnerExtraBoss5::SpawnBullet()
{
	sf::Vector2f position = mOwner->getPosition();

	for (int i = 0; i < 8; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 300.0f, sf::Vector2f(cos(i * std::numbers::pi / 4 + mRotation), sin(i * std::numbers::pi / 4 + mRotation)), position, 0, BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}
}

void BulletSpawnerExtraBoss5::Update(float dt)
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
