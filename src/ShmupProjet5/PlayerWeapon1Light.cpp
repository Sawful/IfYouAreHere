#include "SFML/Graphics.hpp"
#include "PlayerWeapon1Light.h"
#include "GameManager.h"
#include "SceneManager.h"

PlayerWeapon1Light::PlayerWeapon1Light(Character* owner): PlayerWeapon(owner, 0.1f)
{
}

void PlayerWeapon1Light::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(2, 800.0f, sf::Vector2f(0.0f, -1.0f), getPosition(), 0, BULLET_LIGHT_1, PLAYERBULLET, true, 8.0f));
}
