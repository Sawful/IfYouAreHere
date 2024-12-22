#include "PlayerWeapon4ALight.h"
#include <numbers>
#include "BulletBase.h"

PlayerWeapon4ALight::PlayerWeapon4ALight(Character* owner) : PlayerWeapon(owner, 0.2f)
{
	mBulletTexture.loadFromFile("..\\..\\..\\res\\lightbullet2.png");
}

void PlayerWeapon4ALight::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(4, 800.0f, sf::Vector2f(cos(265 * std::numbers::pi / 180), sin(265 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(50.0f, 20.0f), -10, &mBulletTexture, PLAYERBULLET, true, 8.0f));
	mCurrentStage->AddToEntities(new BulletBase(4, 800.0f, sf::Vector2f(cos(275 * std::numbers::pi / 180), sin(275 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(-50.0f, 20.0f), 10, &mBulletTexture, PLAYERBULLET, true, 8.0f));
}
