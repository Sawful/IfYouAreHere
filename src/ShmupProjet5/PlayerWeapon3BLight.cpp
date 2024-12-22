#include "PlayerWeapon3BLight.h"
#include "BulletAccelerate.h"

PlayerWeapon3BLight::PlayerWeapon3BLight(Character* owner) : PlayerWeapon(owner, 0.15f)
{

}

void PlayerWeapon3BLight::Shoot()
{
	mCurrentStage->AddToEntities(new BulletAccelerate(2, 100.0f, sf::Vector2f(0.0f, -1.0f), getPosition() + sf::Vector2f(20.0f, 20.0f), 0, BULLET_LIGHT_3, PLAYERBULLET, true, 2400, 1));
	mCurrentStage->AddToEntities(new BulletAccelerate(2, 100.0f, sf::Vector2f(0.0f, -1.0f), getPosition() + sf::Vector2f(-20.0f, 20.0f), 0, BULLET_LIGHT_3, PLAYERBULLET, true, 2400, 1));
}
