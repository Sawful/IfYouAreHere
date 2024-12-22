#include "PlayerWeapon2Light.h"
#include "GameManager.h"
#include "SceneManager.h"


PlayerWeapon2Light::PlayerWeapon2Light(Character* owner) : PlayerWeapon(owner, 0.12f)
{
}

void PlayerWeapon2Light::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(1, 800.0f, sf::Vector2f(0.0f, -1.0f), getPosition() + sf::Vector2f(10.0f, 20.0f), 0, BULLET_LIGHT_1, PLAYERBULLET, true, 8.0f));
	mCurrentStage->AddToEntities(new BulletBase(1, 800.0f, sf::Vector2f(0.0f, -1.0f), getPosition() + sf::Vector2f(-10.0f, 20.0f), 0, BULLET_LIGHT_1, PLAYERBULLET, true, 8.0f));
}
