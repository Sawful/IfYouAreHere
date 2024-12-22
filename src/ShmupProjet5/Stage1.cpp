#include "Stage1.h"
#include "GameManager.h"
#include "ShotSlug1.h"
#include "BigCircleGuy.h"
#include "TripleShotCritter.h"
#include "Boss1.h"


Stage1::Stage1(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm) : Level(window, playerController, gm)
{
	mShotSlugTexture.loadFromFile("..\\..\\..\\res\\enemy_critter1_st.png");
	mCircleGuyTexture.loadFromFile("..\\..\\..\\res\\enemy_circle_all.png");
	mTripleShotTexture.loadFromFile("..\\..\\..\\res\\bigger_enemy_critter3_triple_idle.png");
	mBossTexture.loadFromFile("..\\..\\..\\res\\critterboss.png");

	mForest.loadFromFile("../../../res/shroomforest_bg.png");

	mBackground1.setTextureRect(sf::IntRect(0, 0, 800, 1600));
	mBackground1.setTexture(mForest);
	mBackground1.setPosition(0, -800);

	mBackground2.setTextureRect(sf::IntRect(0, 0, 800, 1600));
	mBackground2.setTexture(mForest);
	mBackground2.setPosition(0, -2400); 
}

void Stage1::Update(float deltaTime)
{
	Level::Update(deltaTime);

	//VVV Background looping VVV
	//When a Background's y reaches 0, it means the other one is out of the view
	//So we bring it back up to keep the loop
	mBackground1.setPosition(mBackground1.getPosition() + (sf::Vector2f(0, 200)*deltaTime));
	mBackground2.setPosition(mBackground2.getPosition() + (sf::Vector2f(0, 200)*deltaTime));

	if (0 <= mBackground2.getPosition().y && mBackground2.getPosition().y <= 800) {
		mBackground1.setPosition(mBackground2.getPosition() + sf::Vector2f(0, -1600));
	}
	if (0 <= mBackground1.getPosition().y && mBackground1.getPosition().y <= 800) {
		mBackground2.setPosition(mBackground1.getPosition() + sf::Vector2f(0, -1600));
	}

	PlayLevel(deltaTime);
}

void Stage1::SpawnWave(int wave)
{
	std::vector<Path*> wavePath;

	switch (wave)
	{
	case 1:
	case 2:
	case 3:
		wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 300.0f), sf::Vector2f(-700.0f, 0.0f), 7.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(150.0f, 300.0f), sf::Vector2f(0.0f, 300.0f), sf::Vector2f(0.0f, 500.0f), sf::Vector2f(150.0f, 500.0f), 3.0f));
		wavePath.push_back(new LinePath(sf::Vector2f(150.0f, 500.0f), sf::Vector2f(700.0f, 0.0f), 7.0f));

		AddToEntities(new ShotSlug1(sf::Vector2f(850.0f, 300.0f), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 1.0f;
		break;

	case 4:
		wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 300.0f), sf::Vector2f(-700.0f, 0.0f), 7.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(150.0f, 300.0f), sf::Vector2f(0.0f, 300.0f), sf::Vector2f(0.0f, 500.0f), sf::Vector2f(150.0f, 500.0f), 3.0f));
		wavePath.push_back(new LinePath(sf::Vector2f(150.0f, 500.0f), sf::Vector2f(700.0f, 0.0f), 7.0f));

		AddToEntities(new ShotSlug1(sf::Vector2f(850.0f, 300.0f), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 6.0f;
		break;

	case 5:
	case 6:
	case 7:
		wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 500.0f), sf::Vector2f(700.0f, 0.0f), 7.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(650.0f, 500.0f), sf::Vector2f(800.0f, 500.0f), sf::Vector2f(800.0f, 300.0f), sf::Vector2f(650.0f, 300.0f), 3.0f));
		wavePath.push_back(new LinePath(sf::Vector2f(650.0f, 300.0f), sf::Vector2f(-700.0f, 0.0f), 7.0f));

		AddToEntities(new ShotSlug1(sf::Vector2f(-50.0f, 500.0f), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 1.0f;
		break;

	case 8:
		wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 500.0f), sf::Vector2f(700.0f, 0.0f), 7.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(650.0f, 500.0f), sf::Vector2f(800.0f, 500.0f), sf::Vector2f(800.0f, 300.0f), sf::Vector2f(650.0f, 300.0f), 3.0f));
		wavePath.push_back(new LinePath(sf::Vector2f(650.0f, 300.0f), sf::Vector2f(-700.0f, 0.0f), 7.0f));

		AddToEntities(new ShotSlug1(sf::Vector2f(-50.0f, 500.0f), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 6.0f;
		break;

	case 9:
	case 11:
	case 13:
		wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 400.0f), sf::Vector2f(-150.0f, 0.0f), 1.0f));
		for (int i = 0; i < 6; i++)
		{
			wavePath.push_back(new PointPath(sf::Vector2f(700.0f - 150.0f * i, 400.0f), 1.0f));

			wavePath.push_back(new LinePath(sf::Vector2f(700.0f - 150.0f * i, 400.0f), sf::Vector2f(-150.0f, 0.0f), 1.0f));
		}

		AddToEntities(new BigCircleGuy(sf::Vector2f(850.0f, 400.0f), 0, true, &mCircleGuyTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 2.0f;

		break;

	case 10:
	case 12:
		wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 400.0f), sf::Vector2f(150.0f, 0.0f), 1.0f));
		for (int i = 0; i < 6; i++)
		{
			wavePath.push_back(new PointPath(sf::Vector2f(100.0f + 150.0f * i, 400.0f), 1.0f));

			wavePath.push_back(new LinePath(sf::Vector2f(100.0f + 150.0f * i, 400.0f), sf::Vector2f(150.0f, 0.0f), 1.0f));
		}

		AddToEntities(new BigCircleGuy(sf::Vector2f(-50.0f, 400.0f), 0, true, &mCircleGuyTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 2.0f;

		break;

	case 14:
		wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 400.0f), sf::Vector2f(150.0f, 0.0f), 1.0f));
		for (int i = 0; i < 6; i++)
		{
			wavePath.push_back(new PointPath(sf::Vector2f(100.0f + 150.0f * i, 400.0f), 1.0f));

			wavePath.push_back(new LinePath(sf::Vector2f(100.0f + 150.0f * i, 400.0f), sf::Vector2f(150.0f, 0.0f), 1.0f));
		}

		AddToEntities(new BigCircleGuy(sf::Vector2f(-50.0f, 400.0f), 0, true, &mCircleGuyTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 5.0f;

		break;

	case 15:
		for (int i = 0; i < 3; i++)
		{
			wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 350.0f + 50.0f * i), sf::Vector2f(-900.0f, 0.0f), 9.0f));
			AddToEntities(new ShotSlug1(sf::Vector2f(850.0f, 350.0f + 50.0f * i), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));
			wavePath.clear();
		}

		for (int i = 0; i < 3; i++)
		{
			wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 350.0f + 50.0f * i), sf::Vector2f(900.0f, 0.0f), 9.0f));
			AddToEntities(new ShotSlug1(sf::Vector2f(-50.0f, 350.0f + 50.0f * i), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));
			wavePath.clear();
		}
		mTimeUntilNextWave = 5.0f;
		break;

	case 16:
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(850.0f, 400.0f), sf::Vector2f(850.0f, 500.0f), sf::Vector2f(550.0f, 500.0f), sf::Vector2f(550.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(550.0f, 400.0f), sf::Vector2f(550.0f, 300.0f), sf::Vector2f(250.0f, 300.0f), sf::Vector2f(250.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(250.0f, 400.0f), sf::Vector2f(250.0f, 500.0f), sf::Vector2f(-50.0f, 500.0f), sf::Vector2f(-50.0f, 400.0f), 6.0f));

		AddToEntities(new TripleShotCritter(sf::Vector2f(850.0f, 400.0f), 0, true, &mTripleShotTexture, &mDropTexture, wavePath));

		wavePath.clear();

		wavePath.push_back(new BezierCurvePath(sf::Vector2f(-50.0f, 400.0f), sf::Vector2f(-50.0f, 300.0f), sf::Vector2f(250.0f, 300.0f), sf::Vector2f(250.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(250.0f, 400.0f), sf::Vector2f(250.0f, 500.0f), sf::Vector2f(550.0f, 500.0f), sf::Vector2f(550.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(550.0f, 400.0f), sf::Vector2f(550.0f, 300.0f), sf::Vector2f(850.0f, 300.0f), sf::Vector2f(850.0f, 400.0f), 6.0f));

		AddToEntities(new TripleShotCritter(sf::Vector2f(-50.0f, 400.0f), 0, true, &mTripleShotTexture, &mDropTexture, wavePath));

		mTimeUntilNextWave = 5.0f;

		break;

	case 17:
		for (int i = 0; i < 2; i++)
		{
			wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 50.0f + 50.0f * i), sf::Vector2f(900.0f, 0.0f), 18.0f));
			AddToEntities(new ShotSlug1(sf::Vector2f(-50.0f, 50.0f), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));
			wavePath.clear();
		}
		
		mTimeUntilNextWave = 9.0f;
		break;

	case 18:
		for (int i = 0; i < 2; i++)
		{
			wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 700.0f + 50.0f * i), sf::Vector2f(-900.0f, 0.0f), 18.0f));
			AddToEntities(new ShotSlug1(sf::Vector2f(850.0f, 700.0f), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));
			wavePath.clear();
		}

		mTimeUntilNextWave = 9.0f;
		break;

	case 19:
		for (int i = 0; i < 2; i++)
		{
			wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 375.0f + 50.0f * i), sf::Vector2f(-900.0f, 0.0f), 9.0f));
			AddToEntities(new ShotSlug1(sf::Vector2f(850.0f, 375.0f + 50.0f * i), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));
			wavePath.clear();
		}

		for (int i = 0; i < 2; i++)
		{
			wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 375.0f + 50.0f * i), sf::Vector2f(900.0f, 0.0f), 9.0f));
			AddToEntities(new ShotSlug1(sf::Vector2f(-50.0f, 375.0f + 50.0f * i), 0, true, &mShotSlugTexture, &mDropTexture, wavePath));
			wavePath.clear();
		}
		mTimeUntilNextWave = 6.0f;
		break;

	case 20:
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(850.0f, 400.0f), sf::Vector2f(850.0f, 500.0f), sf::Vector2f(550.0f, 500.0f), sf::Vector2f(550.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(550.0f, 400.0f), sf::Vector2f(550.0f, 300.0f), sf::Vector2f(250.0f, 300.0f), sf::Vector2f(250.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(250.0f, 400.0f), sf::Vector2f(250.0f, 500.0f), sf::Vector2f(-50.0f, 500.0f), sf::Vector2f(-50.0f, 400.0f), 6.0f));

		AddToEntities(new TripleShotCritter(sf::Vector2f(850.0f, 400.0f), 0, true, &mTripleShotTexture, &mDropTexture, wavePath));

		wavePath.clear();

		wavePath.push_back(new BezierCurvePath(sf::Vector2f(50.0f, 400.0f), sf::Vector2f(50.0f, 300.0f), sf::Vector2f(250.0f, 300.0f), sf::Vector2f(250.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(250.0f, 400.0f), sf::Vector2f(250.0f, 500.0f), sf::Vector2f(550.0f, 500.0f), sf::Vector2f(550.0f, 400.0f), 6.0f));
		wavePath.push_back(new BezierCurvePath(sf::Vector2f(550.0f, 400.0f), sf::Vector2f(550.0f, 300.0f), sf::Vector2f(850.0f, 300.0f), sf::Vector2f(850.0f, 400.0f), 6.0f));

		AddToEntities(new TripleShotCritter(sf::Vector2f(50.0f, 400.0f), 0, true, &mTripleShotTexture, &mDropTexture, wavePath));
		mTimeUntilNextWave = 12.0f;
		break;

	case 21:
		wavePath.push_back(new LinePath(sf::Vector2f(850.0f, 350.0f), sf::Vector2f(-900.0f, 0.0f), 9.0f));
		AddToEntities(new BigCircleGuy(sf::Vector2f(850.0f, 400.0f), 0, true, &mCircleGuyTexture, &mDropTexture, wavePath));
		wavePath.clear();
		wavePath.push_back(new LinePath(sf::Vector2f(-50.0f, 450.0f), sf::Vector2f(900.0f, 0.0f), 9.0f));
		AddToEntities(new BigCircleGuy(sf::Vector2f(-50.0f, 400.0f), 0, true, &mCircleGuyTexture, &mDropTexture, wavePath));
		mTimeUntilNextWave = 10.0f;
		break;

	case 22:
		// Boss
		mGameManager->GetSoundManager()->ChangeMusic(STAGE1BOSS);

		AddToEntities(new Boss1(sf::Vector2f(850.0f, 400.0f), 0, true, &mBossTexture, &mDropTexture));

		break;
	}

}

void Stage1::PlayLevel(float deltaTime)
{
	mTimeUntilNextWave -= deltaTime;

	if (mTimeUntilNextWave <= 0)
	{
		SpawnWave(mWave);
		mWave++;
	}

	Level::PlayLevel(deltaTime);
}

void Stage1::ResetScene()
{
	Level::ResetScene();
	mWave = 1;
}

void Stage1::Draw()
{
	Level::Draw();

	mCurrentWindow->draw(mBackground1);
	mCurrentWindow->draw(mBackground2);

	for (int i = 0; i < entities.size(); i++)
	{
		if (!entities[i]->IsEntityActive())
		{
			continue;
		}

		mCurrentWindow->draw(*entities[i]);
	}
}

void Stage1::EnterScene()
{
	mGameManager->GetSoundManager()->ChangeMusic(STAGE1);

	mTimeUntilNextWave = 2.0f;
	// Remember to put this back to 1 after debug
	mWave = 1;

	AddToEntities(mPlayerController);
	AddToEntities(mPlayerController->GetPlayers()[0]);
	AddToEntities(mPlayerController->GetPlayers()[1]);

	/*for (int i = 0; i < 32; i++)
	{
		mPlayerController->IncreaseWeaponPower(1);
	}*/

	mPlayerController->GetPlayers()[0]->setPosition(sf::Vector2f(400.0f, 700.0f));
	mPlayerController->GetPlayers()[1]->setPosition(sf::Vector2f(400.0f, 100.0f));

	mStageTimer.restart();
}


