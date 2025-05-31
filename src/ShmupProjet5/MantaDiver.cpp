#include "MantaDiver.h"

MantaDiver::MantaDiver(sf::Vector2f position, float rotation, bool isActive, TextureName texture, std::vector<Path*> movementPath):
	Enemy(position, rotation, 1, texture, isActive)
{
	mMovementPath = movementPath;
	//mBulletSpawnerPTR = new BulletSpawnerSlug1(this, mCurrentStage);

	mHealth = 20;

	scoreValue = 10;

	//mSprite.setOrigin(sf::Vector2f(28.0f, 24.0f));

	mHitbox.AddCircle(new sf::CircleShape(28.0f));
}

void MantaDiver::Update(float deltaTime)
{
	//mBulletSpawnerPTR->Update(deltaTime);
	Move(deltaTime);
}

void MantaDiver::Attack()
{
}

void MantaDiver::Move(float deltaTime)
{
	if (mMovementPath[mPathNumber]->LerpFollowPath(deltaTime, this))
	{
		mPathNumber++;

		// Enemy disappears when they finish their path
		if (mPathNumber >= mMovementPath.size())
		{
			// Send self to player
			
		}
	}
}