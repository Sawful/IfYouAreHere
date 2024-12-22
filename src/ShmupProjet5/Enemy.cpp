#include "Enemy.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Drop.h"

Enemy::Enemy(sf::Vector2f position, float rotation, int dropAmount, TextureName texture, bool isActive):
	Character(position, rotation, texture, ENEMYTAG, isActive)
{
	mPathNumber = 0;

	mGameManager = GameManager::GetInstance();
	mSoundManager = mGameManager->GetSoundManager();

	mDropAmount = dropAmount;

	mCurrentStage = mGameManager->GetSceneManager()->GetCurrentStage();

	mDropTexture = mGameManager->GetResourceManager()->GetTexture(DROP_TEXTURE);
}

void Enemy::TakeDamage(int damage)
{
	mHealth -= damage;

	mSoundManager->PlaySound(HITSOUND);

	mGameManager->RaiseScore(scoreValue * damage);

	if (mHealth <= 0)
	{
		mSoundManager->PlaySound(ENEMYDEATHSOUND);

		Die();
	}
}

void Enemy::Die()
{
	SetEntityActive(false);

	// Drop (done)
	for(int i = 0; i < mDropAmount; i++)
	{
		mCurrentStage->AddToEntities(new Drop(getPosition(), 15.0f, DROP_TEXTURE));
	}

	// Death vfx / sfx

	
	// Give points (done)
	mGameManager->RaiseScore(scoreValue * 10);
}

void Enemy::Move(float deltaTime)
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
