#include "PlayerWeapon4BDark.h"
#include "BulletBase.h"
#include <numbers>

PlayerWeapon4BDark::PlayerWeapon4BDark(Character* owner) : PlayerWeapon(owner, 0.06f)
{
}

void PlayerWeapon4BDark::Shoot()
{
	mCurrentStage->AddToEntities(new BulletBase(1, 800.0f, sf::Vector2f(cos(95 * std::numbers::pi / 180), sin(95 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(0.0f, 0.0f), 190, BULLET_DARK_3, PLAYERBULLET, true, 8.0f));
	mCurrentStage->AddToEntities(new BulletBase(1, 800.0f, sf::Vector2f(cos(85 * std::numbers::pi / 180), sin(85 * std::numbers::pi / 180)), getPosition() + sf::Vector2f(0.0f, 0.0f), -190, BULLET_DARK_3, PLAYERBULLET, true, 8.0f));
}
