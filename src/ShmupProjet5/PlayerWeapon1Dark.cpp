#include "PlayerWeapon1Dark.h"
#include "GameManager.h"
#include "SceneManager.h"

PlayerWeapon1Dark::PlayerWeapon1Dark(Character* owner) : PlayerWeapon(owner, 0.1f)
{
	mBulletTexture.loadFromFile("..\\..\\..\\res\\darkbullet.png");
}

void PlayerWeapon1Dark::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(2, 800.0f, sf::Vector2f(0.0f, 1.0f), getPosition(), 0,  &mBulletTexture, PLAYERBULLET, true, 8.0f));
}

