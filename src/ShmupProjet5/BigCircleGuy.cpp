#include "BigCircleGuy.h"
#include "GameManager.h"
#include "SceneManager.h"

BigCircleGuy::BigCircleGuy(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture, std::vector<Path*> movementPath):
	Enemy(position, rotation, 2, texture, dropTexture, isActive)
{
	mTexture = texture;
	mMovementPath = movementPath;
	mBulletSpawnerPTR = new BulletSpawnerCircle1(this, mCurrentStage);

	mHealth = 10;

	scoreValue = 10;

	mSprite.setOrigin(sf::Vector2f(21.0f, 25.0f));
	mSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	mAttacking = false;

	mHitbox.AddCircle(new sf::CircleShape(28.0f));
}

void BigCircleGuy::Update(float deltaTime)
{
	mBulletSpawnerPTR->Update(deltaTime);
	Move(deltaTime);
	mAttackAnimationTime -= deltaTime;

	if (mAttackAnimationTime <= 0.0f && mAttacking)
	{
		mSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		mAttacking = false;
	}
}

void BigCircleGuy::Attack()
{
	mAttackAnimationTime = 0.5f;
	mAttacking = true;
	mSprite.setTextureRect(sf::IntRect(50, 0, 50, 50));
}
