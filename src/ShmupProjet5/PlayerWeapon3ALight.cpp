#include "PlayerWeapon3ALight.h"
#include "GameManager.h"
#include "SceneManager.h"
#include <numbers>

PlayerWeapon3ALight::PlayerWeapon3ALight(Character* owner) : PlayerWeapon(owner, 0.2f)
{
	mBulletTexture.loadFromFile("..\\..\\..\\res\\lightbullet2.png");
}

void PlayerWeapon3ALight::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(3, 800.0f, sf::Vector2f(cos(267 * std::numbers::pi /180), sin(267 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(30.0f, 10.0f), -6, &mBulletTexture, PLAYERBULLET, true, 8.0f));
	mCurrentStage->AddToEntities(new BulletBase(3, 800.0f, sf::Vector2f(cos(273 * std::numbers::pi / 180), sin(273 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(-30.0f, 10.0f), 6, &mBulletTexture, PLAYERBULLET, true, 8.0f));
}

