#include "PlayerWeapon3ADark.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "BulletSnake.h"


PlayerWeapon3ADark::PlayerWeapon3ADark(Character* owner) : PlayerWeapon(owner, 0.08f)
{
	mBulletTexture.loadFromFile("..\\..\\..\\res\\darkbullet2.png");
}

void PlayerWeapon3ADark::Shoot()
{
	mCurrentStage->AddToEntities(new BulletSnake(2, 800.0f, sf::Vector2f(0.0f, 1.0f), getPosition() + sf::Vector2f(30.0f, -30.0f), 0, &mBulletTexture, PLAYERBULLET, true, 0.0f));
	mCurrentStage->AddToEntities(new BulletSnake(2, 800.0f, sf::Vector2f(0.0f, 1.0f), getPosition() + sf::Vector2f(-30.0f, -30.0f), 0, &mBulletTexture, PLAYERBULLET, true, 3.1415f));
}
