#pragma once
#include "BulletSpawner.h"
#include "Character.h"
#include "Scene.h"


class PlayerWeapon : public BulletSpawner
{
	Character* mOwner;

	sf::Clock mTimer;
	float mShootCooldown;

protected:
	sf::Texture mBulletTexture;

public:
	PlayerWeapon(Character* owner, float shootCooldown);
	virtual void Update(float deltaTime);
	virtual void Shoot() = 0;
};

