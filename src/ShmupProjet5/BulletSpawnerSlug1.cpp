#include "BulletSpawnerSlug1.h"
#include "BulletBase.h"
#include "Enemy.h"
#include "PlayerController.h"

BulletSpawnerSlug1::BulletSpawnerSlug1(Enemy* owner, Stage* currentStage)
{
	mCurrentStage = currentStage;
	mPlayerController = mCurrentStage->GetPlayerController();

	mOwner = owner;
}

void BulletSpawnerSlug1::SpawnBullet(sf::Vector2f targetPosition)
{
	sf::Vector2f bulletDirection = targetPosition - getPosition();

	bulletDirection = *NormalizeV2f(bulletDirection);

	mCurrentStage->AddToEntities(new BulletBase(1, 200.0f, bulletDirection, getPosition() + sf::Vector2f(-10.0f, 10.0f), getRotation(), BULLET_TEXTURE, ENEMYBULLET, true, 8.0f));
}

void BulletSpawnerSlug1::Update(float dt)
{
	mShotTime -= dt;

	setPosition(mOwner->getPosition());

	if (mShotTime <= 0)
	{
		SpawnBullet(mPlayerController->GetActivePlayerPosition());
		mShotTime = mShotCooldown;
	}
}
