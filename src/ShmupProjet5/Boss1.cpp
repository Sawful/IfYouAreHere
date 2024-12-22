#include "Boss1.h"
#include "BulletSpawnerBoss.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Drop.h"

Boss1::Boss1(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture):
	Enemy(position, rotation, 0, texture, dropTexture, isActive)
{
	mTexture = texture;
	
	mHealth = 4000;
	// Phase 1: 750hp
	// Phase 2: 1250hp
	// Phase 3: 500hp
	// Phase 4: 1500hp

	scoreValue = 20;

	mSprite.setOrigin(sf::Vector2f(35.0f, 23.0f));
	mSprite.setScale(sf::Vector2f(1.5f, 1.5f));

	mHitbox.AddCircle(new sf::CircleShape(48.0f));

	mMovementPathArriving.push_back(new LinePath(sf::Vector2f(850, 400.0f), sf::Vector2f(-450, 0.0f), 2.25f));

	mMovementPathState1.push_back(new PointPath(sf::Vector2f(400.0f, 400.0f), 8.0f));

	mMovementPathState2.push_back(new LinePath(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(100.0f, 0.0f), 4));
	mMovementPathState2.push_back(new LinePath(sf::Vector2f(500.0f, 400.0f), sf::Vector2f(-200.0f, 0.0f), 8));
	mMovementPathState2.push_back(new LinePath(sf::Vector2f(300.0f, 400.0f), sf::Vector2f(100.0f, 0.0f), 4));

	mMovementPathState3.push_back(new BezierCurvePath(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(400.0f, 350.0f), sf::Vector2f(500.0f, 350.0f), sf::Vector2f(500.0f, 400.0f), 2.0f));
	mMovementPathState3.push_back(new BezierCurvePath(sf::Vector2f(500.0f, 400.0f), sf::Vector2f(500.0f, 450.0f), sf::Vector2f(300.0f, 350.0f), sf::Vector2f(300.0f, 400.0f), 4.0f));
	mMovementPathState3.push_back(new BezierCurvePath(sf::Vector2f(300.0f, 400.0f), sf::Vector2f(300.0f, 450.0f), sf::Vector2f(400.0f, 450.0f), sf::Vector2f(400.0f, 400.0f), 2.0f));

	mMovementPathState4.push_back(new PointPath(sf::Vector2f(400.0f, 400.0f), 8.0f));

	mBulletSpawnerState1Main = new BulletSpawnerBoss11Main(this, mCurrentStage);

	mBulletSpawnerState1Sub = new BulletSpawnerBoss11Sub(this);
	mBulletSpawnerState1Sub->SetCurrentStage(mCurrentStage);

	mBulletSpawnerState2 = new BulletSpawnerBoss12(this, mCurrentStage);

	mBulletSpawnerState3 = new BulletSpawnerBoss13(this, mCurrentStage);

	mBulletSpawnerState4 = new BulletSpawnerBoss14(this);
	mBulletSpawnerState4->SetCurrentStage(mCurrentStage);

	mCurrentState = Arriving;

	mCurrentMovementPath = &mMovementPathArriving;
}

void Boss1::Update(float deltaTime)
{
	for (int i = 0; i < mCurrentBulletSpawners.size(); i++)
	{
		mCurrentBulletSpawners[i]->Update(deltaTime);
	}
	
	Move(deltaTime);
}

void Boss1::Attack() // If animation needed;
{
}

void Boss1::Move(float deltaTime)
{
	if (mCurrentState == Arriving)
	{
		if ((*mCurrentMovementPath)[mPathNumber]->FollowPath(deltaTime, this))
		{
			mCurrentBulletSpawners.push_back(mBulletSpawnerState1Main);
			mCurrentBulletSpawners.push_back(mBulletSpawnerState1Sub);

			mCurrentMovementPath = &mMovementPathState1;
			mCurrentState = Phase1;
		}
	}

	else if ((*mCurrentMovementPath)[mPathNumber]->FollowPath(deltaTime, this))
	{
		(*mCurrentMovementPath)[mPathNumber]->ResetCompletion();

		mPathNumber++;
		// Restart Path loop
		if (mPathNumber >= mCurrentMovementPath->size())
		{
			mPathNumber = 0;
		}
	}
}

void Boss1::Die()
{
	SetEntityActive(false);

	// Death effect
	mGameManager->GetSceneManager()->ChangeToStage(1);

	// Give points (done)
	mGameManager->RaiseScore(scoreValue * 10);
}

void Boss1::TakeDamage(int damage)
{
	Enemy::TakeDamage(damage);

	if (mHealth <= 1500 && mCurrentState != Phase4)
	{
		mCurrentState = Phase4;

		mBulletSpawnerState3->RemoveBullets();

		mCurrentBulletSpawners.clear();
		mCurrentBulletSpawners.push_back(mBulletSpawnerState4);
		mCurrentMovementPath = &mMovementPathState4;
		mPathNumber = 0;
	}

	else if (mHealth <= 2000 && mCurrentState != Phase3 && mCurrentState != Phase4)
	{
		mCurrentState = Phase3;
		
		mBulletSpawnerState2->RemoveBullets();

		mCurrentBulletSpawners.clear();
		mCurrentBulletSpawners.push_back(mBulletSpawnerState3);
		mCurrentMovementPath = &mMovementPathState3;
		mPathNumber = 0;
	}

	else if (mHealth <= 3250 && mCurrentState != Phase2 && mCurrentState != Phase3 && mCurrentState != Phase4)
	{
		mCurrentState = Phase2;

		mBulletSpawnerState1Main->RemoveBullets();
		mBulletSpawnerState1Sub->RemoveBullets();

		mCurrentBulletSpawners.clear();
		mCurrentBulletSpawners.push_back(mBulletSpawnerState2);

		mCurrentMovementPath = &mMovementPathState2;
		mPathNumber = 0;
	}
}
