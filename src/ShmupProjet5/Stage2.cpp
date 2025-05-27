#include "Stage2.h"
#include "GameManager.h"
#include "ShotSlug1.h"
#include "BigCircleGuy.h"
#include "TripleShotCritter.h"

Stage2::Stage2(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm) : Stage(window, playerController, gm)
{
	mBackgroundTexture.loadFromFile("../../../res/shroomforest_bg.png");

	mBackground1.setTextureRect(sf::IntRect(0, 0, 800, 1600));
	mBackground1.setTexture(mBackgroundTexture);
	mBackground1.setPosition(0, -800);

	mBackground2.setTextureRect(sf::IntRect(0, 0, 800, 1600));
	mBackground2.setTexture(mBackgroundTexture);
	mBackground2.setPosition(0, -2400);
}

void Stage2::SpawnWave(int wave)
{
	std::vector<Path*> wavePath;

	switch (wave)
	{
	case 1:
		break;
	}
}

void Stage2::Update(float deltaTime)
{
	Stage::Update(deltaTime);

	//VVV Background looping VVV
	//When a Background's y reaches 0, it means the other one is out of the view
	//So we bring it back up to keep the loop
	mBackground1.setPosition(mBackground1.getPosition() + (sf::Vector2f(0, 200) * deltaTime));
	mBackground2.setPosition(mBackground2.getPosition() + (sf::Vector2f(0, 200) * deltaTime));

	if (0 <= mBackground2.getPosition().y && mBackground2.getPosition().y <= 800) {
		mBackground1.setPosition(mBackground2.getPosition() + sf::Vector2f(0, -1600));
	}
	if (0 <= mBackground1.getPosition().y && mBackground1.getPosition().y <= 800) {
		mBackground2.setPosition(mBackground1.getPosition() + sf::Vector2f(0, -1600));
	}

	PlayStage(deltaTime);
}

void Stage2::Draw()
{
	Stage::Draw();

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

void Stage2::EnterScene()
{
	mGameManager->GetSoundManager()->ChangeMusic(STAGE1);
	mTimeUntilNextWave = 2.0f;
	Stage::EnterScene();

	// Remember to put this back to 1 (or remove line) after debug
	mWave = 1;
}