#include "Stage2.h"
#include "GameManager.h"
#include "Boss2.h"
#include "Drop.h"

Stage2::Stage2(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm) : Level(window, playerController, gm)
{
	mBossTexture.loadFromFile("..\\..\\..\\res\\parhelions.png");

	mSpace.loadFromFile("../../../res/background_stage2.png");

	//mBackground1.setTextureRect(sf::IntRect(0, 0, 800, 1600));
	mBackground1.setTexture(mSpace);
	mBackground1.setScale(sf::Vector2f(1.5f, 1.5f));
	mBackground1.setPosition(-200, -800);

	//mBackground2.setTextureRect(sf::IntRect(0, 0, 800, 1600));
	mBackground2.setTexture(mSpace);
	mBackground2.setScale(sf::Vector2f(1.5f, 1.5f));
	mBackground2.setPosition(-200, -3200);

	mShakeVectors.push_back(new sf::Vector2f(2, 0));
	mShakeVectors.push_back(new sf::Vector2f(-2, -2));
	mShakeVectors.push_back(new sf::Vector2f(2, 0));
	mShakeVectors.push_back(new sf::Vector2f(-2, 2));
}

void Stage2::Update(float deltaTime)
{
	if (mIsUnzooming)
	{
		sf::Vector2f newSize = mGameView.getSize() + sf::Vector2f(8.0f, 8.0f) * deltaTime;
		sf::FloatRect newRect = mPlayerController->GetGameScreen();
		if (newSize.x >= 1200)
		{
			newSize = sf::Vector2f(1200.0f, 1200.0f);
		}

		else
		{
			newRect.left -= 4.0f * deltaTime;
			newRect.top -= 4.0f * deltaTime;
			newRect.width += 8.0f * deltaTime;
			newRect.height += 8.0f * deltaTime;
		}

		mPlayerController->SetGameScreen(newRect);
		mGameView.setSize(newSize);
	}

	else if(mIsUnzoomingInitial)
	{
		mGameView.setSize(mGameView.getSize() + sf::Vector2f(30.0f, 30.0f) * deltaTime);

		if (mGameView.getSize().x >= 800)
		{
			mGameView.setSize(sf::Vector2f(800.0f, 800.0f));
			mIsUnzoomingInitial = false;
		}
	}

	if (mIsShaking)
	{
		mShakeTime -= deltaTime;
		mShakeDuration -= deltaTime;

		if (mShakeDuration <= 0)
		{
			mIsShaking = false;
		}

		if (mShakeTime <= 0)
		{
			mGameView.setCenter(mGameView.getCenter() + *mShakeVectors[mShakeVectorIndex]);
			mShakeVectorIndex++;

			mShakeTime = mShakeCooldown;

			if (mShakeVectorIndex >= 4)
			{
				mShakeVectorIndex = 0;
			}
		}
	}

	Level::Update(deltaTime);

	//VVV Background looping VVV
	//When a Background's y reaches 0, it means the other one is out of the view
	//So we bring it back up to keep the loop
	mBackground1.setPosition(mBackground1.getPosition() + (sf::Vector2f(0, 50) * deltaTime));
	mBackground2.setPosition(mBackground2.getPosition() + (sf::Vector2f(0, 50) * deltaTime));

	if (-400 <= mBackground2.getPosition().y && mBackground2.getPosition().y <= 400) {
		mBackground1.setPosition(mBackground2.getPosition() + sf::Vector2f(0, -2400));
	}
	if (-400 <= mBackground1.getPosition().y && mBackground1.getPosition().y <= 400) {
		mBackground2.setPosition(mBackground1.getPosition() + sf::Vector2f(0, -2400));
	}

	PlayLevel(deltaTime);
}

void Stage2::SpawnWave(int wave)
{
	
}

void Stage2::AddToEntities(Bullet* entity)
{
	entity->SetGameRectBig(mIsUnzooming);

	entities.push_back(entity);

	if (entity->GetOwnerType() == PLAYER)
	{
		mPlayerBullets.push_back(entity);
	}
	else
	{
		mEnemyBullets.push_back(entity);
	}
}

void Stage2::AddToEntities(Enemy* entity)
{
	entities.push_back(entity);
	mEnemies.push_back(entity);
}

void Stage2::AddToEntities(Drop* entity)
{
	entities.push_back(entity);
	mEnemyDrops.push_back(entity);
}

void Stage2::AddToEntities(Entity* entity)
{
	entities.push_back(entity);
}


void Stage2::PlayLevel(float deltaTime)
{
	Level::PlayLevel(deltaTime);

}

void Stage2::ResetScene()
{
	mPlayerController->SetGameScreen(sf::FloatRect(24, 32, 752, 736));
	mGameView.setSize(sf::Vector2f(800.0f, 800.0f));
	mGameView.setCenter(sf::Vector2f(400.0f, 400.0f));
	mIsShaking = false;
	mIsUnzooming = false;
	Level::ResetScene();
}

void Stage2::Draw()
{
	// Draw Scoring
	Level::Draw();

	// Draw Background
	mCurrentWindow->draw(mBackground1);
	mCurrentWindow->draw(mBackground2);

	// Draw Entities
	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->IsEntityActive())
		{
			continue;
		}

		mCurrentWindow->draw(*entities[i]);
	}
}

void Stage2::EnterScene()
{
	mGameManager->GetSoundManager()->ChangeMusic(STAGE2BOSS);

	mGameView.setSize(sf::Vector2f(64.0f, 64.0f));
	mIsUnzoomingInitial = true;

	AddToEntities(mPlayerController);
	AddToEntities(mPlayerController->GetPlayers()[0]);
	AddToEntities(mPlayerController->GetPlayers()[1]);

	mPlayerController->GetPlayers()[0]->setPosition(sf::Vector2f(400.0f, 700.0f));
	mPlayerController->GetPlayers()[1]->setPosition(sf::Vector2f(400.0f, 100.0f));

	AddToEntities(new Boss2(sf::Vector2f(400.0f, 400.0f), 0, true, PARHELION_TEXTURE));

	mStageTimer.restart();
}

void Stage2::SetShake(float duration)
{
	mIsShaking = true;
	mShakeDuration = duration;
}

void Stage2::SetBoss2Unzoom()
{
	mIsUnzooming = true;
}
