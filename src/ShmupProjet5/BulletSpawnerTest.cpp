#include "BulletSpawnerTest.h"
#include "Enemy.h"
#include "GameManager.h"
#include "SceneManager.h"


BulletSpawnerTest::BulletSpawnerTest(Enemy* owner) : BulletSpawner()
{
	mPlayerController = mCurrentStage->GetPlayerController();

	mOwner = owner;

	mBulletTexture.loadFromFile("..\\..\\..\\res\\bullet.png");
}

void BulletSpawnerTest::SpawnBullet(sf::Vector2f targetPosition)
{
	sf::Vector2f bulletDirection = targetPosition - getPosition();

	//Normalize direction vector
	float len = sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
	if (len != 0) {
		bulletDirection.x = bulletDirection.x / len;
		bulletDirection.y = bulletDirection.y / len;
	}
	
	//InstantiateBullet(150.0f, bulletDirection, getPosition(), getRotation(), &mBulletTexture);

	mCurrentStage->AddToEntities(new BulletBase(1, 150.0f, bulletDirection, getPosition(), getRotation(), &mBulletTexture, ENEMYBULLET, true, 8.0f));
}

void BulletSpawnerTest::Update(float dt)
{
	setPosition(mOwner->getPosition());

	if (mShotCooldownClock.getElapsedTime().asSeconds() >= mShotCooldown)
	{
		SpawnBullet(mPlayerController->GetActivePlayerPosition());
		mShotCooldownClock.restart();
	}
}
