#include "ShotSlug1.h"
#include "BulletSpawnerSlug1.h"
#include "GameManager.h"
#include "SceneManager.h"

ShotSlug1::ShotSlug1(sf::Vector2f position, float rotation, bool isActive, TextureName texture, std::vector<Path*> movementPath):
	Enemy(position, rotation, 1, texture, isActive)
{
	mMovementPath = movementPath;
	mBulletSpawnerPTR = new BulletSpawnerSlug1(this, mCurrentStage);

	mHealth = 8;

	scoreValue = 5;

	mSprite.setOrigin(sf::Vector2f(28.0f, 24.0f));

	mHitbox.AddCircle(new sf::CircleShape(28.0f));
}

void ShotSlug1::Update(float deltaTime)
{
	mBulletSpawnerPTR->Update(deltaTime);
	Move(deltaTime);
}

void ShotSlug1::Attack()
{
}

void ShotSlug1::Move(float deltaTime)
{
	if (mMovementPath[mPathNumber]->FollowPath(deltaTime, this))
	{
		mPathNumber++;

		// Enemy disappears when they finish their path
		if (mPathNumber >= mMovementPath.size())
		{
			SetEntityActive(false);
		}
	}
}
