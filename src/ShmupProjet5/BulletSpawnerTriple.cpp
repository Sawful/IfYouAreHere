#include "BulletSpawnerTriple.h"
#include "BulletBase.h"
#include "Enemy.h"
#include "PlayerController.h"


BulletSpawnerTriple::BulletSpawnerTriple(Enemy* owner, Level* currentStage)
{
	mCurrentStage = currentStage;

	mPlayerController = mCurrentStage->GetPlayerController();

	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");
}

void BulletSpawnerTriple::SpawnBullet(sf::Vector2f targetPosition)
{
	sf::Vector2f bulletDirection = targetPosition - getPosition();

	bulletDirection = *NormalizeV2f(bulletDirection);

	sf::Vector2f bulletDirectionRight = *RotateV2f(bulletDirection, 0.5);
	sf::Vector2f bulletDirectionLeft = *RotateV2f(bulletDirection, -0.5);

	for (int i = 1; i < 4; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 100.0f * i, bulletDirection, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
		mCurrentStage->AddToEntities(new BulletBase(1, 100.0f * i, bulletDirectionRight, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
		mCurrentStage->AddToEntities(new BulletBase(1, 100.0f * i, bulletDirectionLeft, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
	}

	bulletDirection = -bulletDirection;
	bulletDirectionRight = *RotateV2f(bulletDirection, 0.5);
	bulletDirectionLeft = *RotateV2f(bulletDirection, -0.5);

	for (int i = 1; i < 4; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 100.0f * i, bulletDirection, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
		mCurrentStage->AddToEntities(new BulletBase(1, 100.0f * i, bulletDirectionRight, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
		mCurrentStage->AddToEntities(new BulletBase(1, 100.0f * i, bulletDirectionLeft, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
	}
}

void BulletSpawnerTriple::Update(float dt)
{
	mShotTime -= dt;

	setPosition(mOwner->getPosition());

	if (mShotTime <= 0)
	{
		SpawnBullet(mPlayerController->GetActivePlayerPosition());
		mShotTime = mShotCooldown;
	}
}
