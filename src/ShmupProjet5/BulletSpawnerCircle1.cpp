#include "BulletSpawnerCircle1.h"
#include "BulletBase.h"
#include "Enemy.h"
#include <math.h>
#include <numbers>


BulletSpawnerCircle1::BulletSpawnerCircle1(Enemy* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;

	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");
}

void BulletSpawnerCircle1::SpawnBullet()
{
	for (int i = 0; i < 8; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 200.0f, sf::Vector2f(cos(i * std::numbers::pi / 4), sin(i * std::numbers::pi / 4)), getPosition(), getRotation(), BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}

	for (int i = 0; i < 8; i++)
	{
		mCurrentStage->AddToEntities(new BulletBase(1, 125.0f, sf::Vector2f(cos(i * std::numbers::pi / 4 + std::numbers::pi / 8), sin(i * std::numbers::pi / 4 + std::numbers::pi / 8)), getPosition(), getRotation(), BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
	}

	mOwner->Attack();
}

void BulletSpawnerCircle1::Update(float dt)
{
	mShotTime -= dt;

	setPosition(mOwner->getPosition());

	if (mShotTime <= 0)
	{
		SpawnBullet();
		mShotTime = mShotCooldown;
	}
}
