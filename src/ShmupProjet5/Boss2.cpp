#include "Boss2.h"
#include "BulletSpawnerBoss2.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Path.h"

Boss2::Boss2(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture):
	Enemy(position, rotation, 0, texture, dropTexture, isActive)
{
	mPermaClock = sf::Clock();
	mPermaClock.restart();

	mHealth = 8000;
	scoreValue = 20;

	mPreviewRectangle = new sf::RectangleShape(sf::Vector2f(780.0f, 280.0f));

	mPreviewRectangle->setOrigin(sf::Vector2f(0.0f, 140.0f));
	mPreviewRectangle->setFillColor(sf::Color::Transparent);
	mPreviewRectangle->setOutlineColor(sf::Color::Transparent);
	mPreviewRectangle->setOutlineThickness(10.0f);

	mLaser = new sf::Sprite;

	mLaserTexture.loadFromFile("..\\..\\..\\res\\laser.png");
	mLaser->setTexture(mLaserTexture);

	mLaser->setScale(sf::Vector2f(12.0f, 3.0f));
	mLaser->setOrigin(sf::Vector2f(0.0f, 50.0f));

	mPermaSpawner = new BulletSpawnerBoss2Phase1Perma(this, mCurrentStage);

	DisplayLaser(false);

	mState = Waiting;
	mPathNumber = 0;

	mPatternWaiting.patternPath.push_back(new PointPath(sf::Vector2f(400.0f, 400.0f), 21.5f));

	mPattern1.patternPath.push_back(new LinePath(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(800.0f, 0.0f), 3));

	mPattern1.patternPath.push_back(new PointPath(sf::Vector2f(1200.0f, 400.0f), 1.0f));
	mPattern1.patternPath.push_back(new LinePath(sf::Vector2f(1200.0f, 400.0f), sf::Vector2f(-1600.0f, 0.0f), 1));

	mPattern1.patternPath.push_back(new PointPath(sf::Vector2f(-400.0f, 400.0f), 1.0f));
	mPattern1.patternPath.push_back(new LinePath(sf::Vector2f(-400.0f, 400.0f), sf::Vector2f(1600.0f, 0.0f), 1));

	mPattern1.patternPath.push_back(new PointPath(sf::Vector2f(1200.0f, 400.0f), 1.0f));
	mPattern1.patternPath.push_back(new LinePath(sf::Vector2f(1200.0f, 400.0f), sf::Vector2f(-1600.0f, 0.0f), 1));

	mPattern1.patternPath.push_back(new PointPath(sf::Vector2f(-400.0f, 400.0f), 1.0f));
	mPattern1.patternPath.push_back(new LinePath(sf::Vector2f(-400.0f, 400.0f), sf::Vector2f(800.0f, 0.0f), 3));

	mPattern1.patternPath.push_back(new PointPath(sf::Vector2f(400.0f, 400.0f), 1.0f));

	mPattern1.patternSpawners.push_back(new BulletSpawnerBoss21(this, mCurrentStage));
	//mPattern1.patternSpawners.push_back(mPermaSpawner);

	mPattern2.patternPath.push_back(new PointPath(sf::Vector2f(400.0f, 400.0f), 5.0f));

	mPattern2.patternSpawners.push_back(new BulletSpawnerBoss22(this, mCurrentStage));
	mPattern2.patternSpawners.push_back(mPermaSpawner);

	mPattern3.patternPath.push_back(new LinePath(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.0f, -150.0f), 0.5f));
	mPattern3.patternPath.push_back(new PointPath(sf::Vector2f(400.0f, 250.0f), 3.0f));
	mPattern3.patternPath.push_back(new LinePath(sf::Vector2f(400.0f, 250.0f), sf::Vector2f(0.0f, 150.0f), 0.5f));

	mPattern3.patternSpawners.push_back(new BulletSpawnerBoss23(this, mCurrentStage));
	mPattern3.patternSpawners.push_back(mPermaSpawner);

	mPattern4.patternPath.push_back(new LinePath(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(0.0f, 150.0f), 0.5f));
	mPattern4.patternPath.push_back(new PointPath(sf::Vector2f(400.0f, 550.0f), 3.0f));
	mPattern4.patternPath.push_back(new LinePath(sf::Vector2f(400.0f, 550.0f), sf::Vector2f(0.0f, -150.0f), 0.5f));

	mPattern4.patternSpawners.push_back(new BulletSpawnerBoss24(this, mCurrentStage));
	mPattern4.patternSpawners.push_back(mPermaSpawner);

	mPattern5.patternPath.push_back(new PointPath(sf::Vector2f(400.0f, 400.0f), 32.0f));
	mPattern5.patternSpawners.push_back(new BulletSpawnerBoss25(this, mCurrentStage));

	mPhase1Patterns.push_back(&mPattern1);
	mPhase1Patterns.push_back(&mPattern2);
	mPhase1Patterns.push_back(&mPattern3);
	mPhase1Patterns.push_back(&mPattern4);

	mCurrentPattern = &mPatternWaiting;

	mSprite.setScale(sf::Vector2f(3, 3));
	mSprite.setOrigin(sf::Vector2f(36, 36));
	mSprite.setTextureRect(sf::IntRect(0, 0, 72, 72));
}

void Boss2::Update(float deltaTime)
{
	for (int i = 0; i < mCurrentPattern->patternSpawners.size(); i++)
	{
		mCurrentPattern->patternSpawners[i]->Update(deltaTime);
	}

	if (mState == Waiting)
	{
		mFaceChangeTimeWaiting -= deltaTime;
		if (mFaceChangeTimeWaiting < 0)
		{
			mFaceChangeTimeWaiting = mFaceChangeCooldownWaiting;
			int currFace = rand() % 4;

			mSprite.setTextureRect(sf::IntRect(72 * currFace, 0, 72, 72));
		}
	}

	if (mState == Phase1)
	{
		if (mPermaClock.getElapsedTime().asSeconds() > mPermaShotHighest + mPermaShotTime)
		{
			mPermaShotHighest += mPermaShotCooldown;
			mPermaSpawner->SpawnBullet();

			int currFace = rand() % 4;

			mSprite.setTextureRect(sf::IntRect(72 * currFace, 0, 72, 72));
			Move(deltaTime);
		}
	}

	if (mState == Phase2)
	{
		mFaceChangeTimeP2 -= deltaTime;
		if (mFaceChangeTimeP2 < 0)
		{
			mFaceChangeTimeP2 = mFaceChangeCooldownP2;
			int currFace = rand() % 4;

			mSprite.setTextureRect(sf::IntRect(72 * currFace, 0, 72, 72));
		}
	}

	Move(deltaTime);
}

void Boss2::Attack()
{
}

void Boss2::Move(float deltaTime)
{
	if (mState == Waiting)
	{
		if (mPatternWaiting.patternPath[0]->FollowPath(deltaTime, this))
		{
			mState = Phase1;
			mCurrentPattern = &mPattern1;
			mHitbox.AddCircle(new sf::CircleShape(60.0f));
		}
	}

	else if(mState == Phase1)
	{
		if (mCurrentPattern->patternPath[mPathNumber]->FollowPath(deltaTime, this))
		{
			(mCurrentPattern->patternPath)[mPathNumber]->ResetCompletion();

			mPathNumber++;
			
			if (mPathNumber >= mCurrentPattern->patternPath.size())
			{
				mPathNumber = 0;

				for (int i = 0; i < mCurrentPattern->patternSpawners.size(); i++)
				{
					mCurrentPattern->patternSpawners[i]->Reset();
				}

				mCurrentPattern = mPhase1Patterns[rand() % mPhase1Patterns.size()];
			}
		}
	}

	else
	{
		if (mCurrentPattern->patternPath[0]->FollowPath(deltaTime, this))
		{
			mCurrentPattern->patternPath[0]->ResetCompletion();
		}

		//Phase 2 Satori time
	}
}

void Boss2::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*mPreviewRectangle);
	target.draw(*mLaser);

	Entity::draw(target, states);
}

void Boss2::Die()
{
	SetEntityActive(false);

	// Death effect
	mGameManager->GetSceneManager()->ChangeToStage(1);

	// Give points (done)
	mGameManager->RaiseScore(scoreValue * 10);
}

void Boss2::TakeDamage(int damage)
{
	if (mHealth <= 5000)
	{
		mState = Phase2;
		mCurrentPattern = &mPattern5;

		mGameManager->GetSceneManager()->ShakeStage2(10000);
		mGameManager->GetSceneManager()->UnzoomStage2();
	}
}

void Boss2::SetPreviewRectangle(bool display, sf::Vector2f position, float rotation)
{
	if (display)
	{
		mPreviewRectangle->setOutlineColor(sf::Color::Red);
	}
	else
	{
		mPreviewRectangle->setOutlineColor(sf::Color::Transparent);
	}

	mPreviewRectangle->setPosition(position);
	mPreviewRectangle->setRotation(rotation);
}

void Boss2::SetPreviewRectangle(bool display)
{
	if (display)
	{
		mPreviewRectangle->setOutlineColor(sf::Color::Red);
	}
	else
	{
		mPreviewRectangle->setOutlineColor(sf::Color::Transparent);
	}
}


void Boss2::DisplayLaser(bool display, sf::Vector2f position, float rotation)
{
	if (display)
	{
		mLaser->setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		mLaser->setColor(sf::Color(255, 255, 255, 0));
	}
	
	mLaser->setPosition(position);
	mLaser->setRotation(rotation);
}

void Boss2::DisplayLaser(bool display)
{
	if (display)
	{
		mLaser->setColor(sf::Color(255, 255, 255, 255));
	}
	else
	{
		mLaser->setColor(sf::Color(255, 255, 255, 0));
	}
}

