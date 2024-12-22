#include "PlayerWeapon4ADark.h"
#include "BulletSnake.h"

PlayerWeapon4ADark::PlayerWeapon4ADark(Character* owner) : PlayerWeapon(owner, 0.08f)
{
	mBulletTexture.loadFromFile("..\\..\\..\\res\\darkbullet2.png");
}

void PlayerWeapon4ADark::Shoot()
{
	mCurrentStage->AddToEntities(new BulletSnake(3, 800.0f, sf::Vector2f(0.0f, 1.0f), getPosition() + sf::Vector2f(30.0f, -30.0f), 0, &mBulletTexture, PLAYERBULLET, true, 3.1415f));
	mCurrentStage->AddToEntities(new BulletSnake(3, 800.0f, sf::Vector2f(0.0f, 1.0f), getPosition() + sf::Vector2f(-30.0f, -30.0f), 0, &mBulletTexture, PLAYERBULLET, true, 0.0f));
}