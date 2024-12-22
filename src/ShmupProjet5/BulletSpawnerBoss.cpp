#include "BulletSpawnerBoss.h"
#include "BulletBase.h"
#include "PlayerController.h"
#include "Enemy.h"
#include <numbers>
#include "BulletSpawnerBoss.h"


BulletSpawnerBoss14::BulletSpawnerBoss14(Enemy* owner)
{
	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");

	mTurningRight = false;

	mAcceleration = 0;
	mAccelerating = true;
}

void BulletSpawnerBoss14::SpawnBullet()
{
	for (int i = 0; i < 32; i++)
	{
		BulletBase* newBullet = new BulletBase(1, 100.0f + mAcceleration, sf::Vector2f(cos(i * std::numbers::pi / 16), sin(i * std::numbers::pi / 16)), getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f);
		mCurrentStage->AddToEntities(newBullet);
		mBullets.push_back(newBullet);
	}

	if (mAccelerating)
	{
		mAcceleration = std::lerp(mAcceleration, 200.0f, 0.05f);

		mShotCooldown = std::lerp(mShotCooldown, 0.2f, 0.05f);
	}

	else
	{
		mAcceleration = std::lerp(mAcceleration, 0.0f, 0.05f);

		mShotCooldown = std::lerp(mShotCooldown, 1, 0.05f);
	}
	
}

void BulletSpawnerBoss14::Update(float dt)
{
	mShotTime -= dt;
	mAccelerationTime -= dt;

	setPosition(mOwner->getPosition());
	
	mTurningRight = false;


	if (mAccelerationTime <= 0)
	{
		mAccelerationTime = mAccelerationCooldown;
		mAccelerating = !mAccelerating;
	}


	for (int i = 0; i < mBullets.size() / 32; i++)
	{
		mTurningRight = !mTurningRight;

		float bulletRotation = std::numbers::pi / 8 * dt;

		if (!mTurningRight)
		{
			bulletRotation = -bulletRotation;
		}

		for (int j = 0; j < 32; j++)
		{
			mBullets[j + 32 * i]->rotate(bulletRotation);
			mBullets[j + 32 * i]->SetDirection(*RotateV2f(mBullets[j + 32 * i]->GetDirection(), bulletRotation));
		}
	}

	if (mShotTime <= 0)
	{
		SpawnBullet();
		mShotTime = mShotCooldown;
	}
}

BulletSpawnerBoss12::BulletSpawnerBoss12(Enemy* owner, Level* currentStage)
{
	mCurrentStage = currentStage;
	mPlayerController = mCurrentStage->GetPlayerController();

	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");
	mAttacking1 = false;
	mAttacking2 = false;
}

void BulletSpawnerBoss12::SpawnBullet()
{
	sf::Vector2f bulletDirection = mPlayerController->GetActivePlayerPosition() - mOwner->getPosition();

	bulletDirection = *NormalizeV2f(bulletDirection);

	float rotationDelta = (rand() % 200 - 100) / 100.0f;
	float speedDelta = (rand() % 180 - 90);

	bulletDirection = *RotateV2f(bulletDirection, rotationDelta);

	BulletBase* newBullet = new BulletBase(1, 220.0f + speedDelta, bulletDirection, mOwner->getPosition(), 0, &mBulletTexture, ENEMYBULLET, true, 8.0f);
	mCurrentStage->AddToEntities(newBullet);
	mBullets.push_back(newBullet);
}

void BulletSpawnerBoss12::RedirectBullets()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		sf::Vector2f bulletDirection = mPlayerController->GetActivePlayerPosition() - mBullets[i]->getPosition();
		bulletDirection = *NormalizeV2f(bulletDirection);

		mBullets[i]->SetDirection(bulletDirection);
	}
}

void BulletSpawnerBoss12::Update(float dt)
{
	mFullAttackTime -= dt;
	mShotTime -= dt;
	mWaitTime -= dt;

	if (!mAttacking1 && mFullAttackTime <= 0.0f)
	{
		mAttacking1 = true;
		mAttacking2 = false;
		mFullAttackTime = mFullAttackCooldown;

		mBullets.clear();
	}

	if (mAttacking1)
	{
		if (mShotTime <= 0)
		{
			SpawnBullet();
			mShotTime = mShotCooldown;
		}

		if (mBullets.size() >= 100)
		{
			mAttacking1 = false;

			mWaitTime = mWaitCooldown;
		}

		for (int i = 0; i < mBullets.size(); i++)
		{
			float newSpeed = mBullets[i]->GetSpeed() - (80.0f * dt) <= 0 ? 0.0f : mBullets[i]->GetSpeed() - (80.0f * dt);

			mBullets[i]->SetSpeed(newSpeed);
		}
	}

	else if (mAttacking2)
	{
		for (int i = 0; i < mBullets.size(); i++)
		{
			float newSpeed = mBullets[i]->GetSpeed() + (100.0f * dt) > 300.0f ? 300.0f : mBullets[i]->GetSpeed() + (100.0f * dt);

			mBullets[i]->SetSpeed(newSpeed);
		}
	}

	else
	{
		for (int i = 0; i < mBullets.size(); i++)
		{
			float newSpeed = mBullets[i]->GetSpeed() - (80.0f * dt) <= 0 ? 0.0f : mBullets[i]->GetSpeed() - (80.0f * dt);

			mBullets[i]->SetSpeed(newSpeed);
		}

		if (mWaitTime < 0.0f)
		{
			mAttacking2 = true;
			RedirectBullets();
		}
	}
}

BulletSpawnerBoss11Main::BulletSpawnerBoss11Main(Enemy* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mPlayerController = mCurrentStage->GetPlayerController();

	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");

	mShotsFired = 0;
}

void BulletSpawnerBoss11Main::SpawnBullet()
{
	sf::Vector2f targetPosition = mPlayerController->GetActivePlayerPosition();
	sf::Vector2f ownerPosition = mOwner->getPosition();

	for (int i = 0; i < 16; i++)
	{
		sf::Vector2f bulletDirection = targetPosition - ownerPosition;

		bulletDirection = *NormalizeV2f(bulletDirection);

		sf::Vector2f bulletOffset = sf::Vector2f(80.0f, 80.0f);

		bulletOffset = *RotateV2f(bulletOffset, i * std::numbers::pi / 8);

		Bullet* newBullet = new BulletBase(1, 200.0f, bulletDirection, ownerPosition + bulletOffset, getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f);

		mBullets.push_back(newBullet);
		mCurrentStage->AddToEntities(newBullet);
	}
}

void BulletSpawnerBoss11Main::Update(float dt)
{
	mShotTime -= dt;
	mMainAttackTime -= dt;

	if (mMainAttackTime <= 0)
	{
		mShotsFired = 0;
		mMainAttackTime = mMainAttackCooldown;
	}

	if (mShotTime <= 0 && mShotsFired < 3)
	{
		SpawnBullet();
		mShotsFired++;
		mShotTime = mShotCooldown;
	}
}

BulletSpawnerBoss11Sub::BulletSpawnerBoss11Sub(Enemy* owner)
{
	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");

	mAttacking = false;
}

void BulletSpawnerBoss11Sub::SpawnBullet()
{
	sf::Vector2f ownerPosition = mOwner->getPosition();
	sf::Vector2f bulletDirection = sf::Vector2f(1, 0);

	float rotation = (rand() % 628) / 100.0f;

	bulletDirection = *RotateV2f(bulletDirection, rotation);

	Bullet* newBullet = new BulletBase(1, 150.0f, bulletDirection, ownerPosition, getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f);

	mBullets.push_back(newBullet);
	mCurrentStage->AddToEntities(newBullet);
}

void BulletSpawnerBoss11Sub::Update(float dt)
{
	mShotTime -= dt;
	mSubAttackTime -= dt;

	mSubAttackDuration -= dt;

	if (mSubAttackTime <= 0 && !mAttacking)
	{
		mAttacking = true;
		mSubAttackDuration = 3.0f;
		mSubAttackTime = mSubAttackCooldown;
	}

	if (mShotTime <= 0 && mAttacking)
	{
		SpawnBullet();
		mShotTime = mShotCooldown;
	}

	if (mSubAttackDuration <= 0 && mAttacking)
	{
		mAttacking = false;

		//mSubAttackTime = mSubAttackCooldown;
	}
}

BulletSpawnerBoss13::BulletSpawnerBoss13(Enemy* owner, Level* currentStage)
{
	mCurrentStage = currentStage;
	mPlayerController = mCurrentStage->GetPlayerController();

	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");

	mSpreading = true;
	mSpread = 1.0f;
}

void BulletSpawnerBoss13::SpawnBullet()
{
	sf::Vector2f targetPosition = mPlayerController->GetActivePlayerPosition();
	sf::Vector2f ownerPosition = mOwner->getPosition();

	float rotation = ((rand() % (int)mSpread) - ((int)mSpread/2)) / 100.0f;

	sf::Vector2f bulletDirection = targetPosition - ownerPosition;

	bulletDirection = *NormalizeV2f(bulletDirection);

	bulletDirection = *RotateV2f(bulletDirection, rotation);

	Bullet* newBullet = new BulletBase(1, 150.0f, bulletDirection, ownerPosition, getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f);

	mBullets.push_back(newBullet);
	mCurrentStage->AddToEntities(newBullet);
}

void BulletSpawnerBoss13::Update(float dt)
{
	mShotTime -= dt;
	mSpreadTime -= dt;

	if (mSpreadTime <= 0)
	{
		mSpreadTime = mSpreadCooldown;
		mSpreading = !mSpreading;
	}

	if (mSpreading)
	{
		mSpread = std::lerp(mSpread, 157.0f, 0.2f * dt);

		mShotCooldown = std::lerp(mShotCooldown, 0.005f, 0.2f * dt);
	}
	else
	{
		mSpread = std::lerp(mSpread, 1.0f, 0.2f * dt);

		mShotCooldown = std::lerp(mShotCooldown, 0.5f, 0.2f * dt);
	}

	if (mShotTime <= 0)
	{
		SpawnBullet();
		mShotTime = mShotCooldown;
	}
}
