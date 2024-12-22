#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(Character* owner, float shootCooldown): BulletSpawner()
{
	mOwner = owner;
	mShootCooldown = shootCooldown;
}

void PlayerWeapon::Update(float deltaTime)
{
	setPosition(mOwner->getPosition());

	float timeElapsedSinceShot = mTimer.getElapsedTime().asSeconds();

	if (timeElapsedSinceShot >= mShootCooldown)
	{
		Shoot();

		mTimer.restart();
	}
}
