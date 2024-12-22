#include "PlayerWeapon3BDark.h"
#include "BulletBase.h"
#include <numbers>

PlayerWeapon3BDark::PlayerWeapon3BDark(Character* owner): PlayerWeapon(owner, 0.08f)
{
}

void PlayerWeapon3BDark::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(1, 800.0f, sf::Vector2f(cos(93 * std::numbers::pi / 180), sin(93 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(0.0f, 0.0f), 186, BULLET_DARK_3, PLAYERBULLET, true, 8.0f));
	mCurrentStage->AddToEntities(new BulletBase(1, 800.0f, sf::Vector2f(cos(87 * std::numbers::pi / 180), sin(87 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(0.0f, 0.0f), -186, BULLET_DARK_3, PLAYERBULLET, true, 8.0f));
}

