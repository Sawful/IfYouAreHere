#include "PlayerWeapon4BLight.h"
#include "BulletAccelerate.h"

PlayerWeapon4BLight::PlayerWeapon4BLight(Character* owner) : PlayerWeapon(owner, 0.15f)
{
	mBulletTexture.loadFromFile("..\\..\\..\\res\\lightbullet3.png");
}

void PlayerWeapon4BLight::Shoot()
{
	mCurrentStage->AddToEntities(new BulletAccelerate(3, 100.0f, sf::Vector2f(0.0f, -1.0f), getPosition() + sf::Vector2f(30.0f, 30.0f), 0, &mBulletTexture, PLAYERBULLET, true, 2400, 1));
	mCurrentStage->AddToEntities(new BulletAccelerate(3, 100.0f, sf::Vector2f(0.0f, -1.0f), getPosition() + sf::Vector2f(-30.0f, 30.0f), 0, &mBulletTexture, PLAYERBULLET, true, 2400, 1));
}
