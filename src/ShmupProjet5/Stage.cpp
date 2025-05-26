#include "Stage.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Enemy.h"
#include "Player.h"
#include "PlayerController.h"
#include "Drop.h"


Stage::Stage(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm): Scene(window)
{
	mGameManager = gm;
	mPlayerController = playerController;

	mGameView = sf::View(sf::FloatRect(0, 0, 800, 800));
	mGameView.setViewport(sf::FloatRect(0.05f, 0.05, 0.675f, 0.9f));

	mScoreView = sf::View(sf::FloatRect(0, 0, 1600, 1200));
	mScoreView.setViewport(sf::FloatRect(0, 0, 1, 1));
	mScoreView.setCenter(sf::Vector2f(800, 600));

	mSky.loadFromFile("../../../res/sky_test.png");
	mSky.setRepeated(true);

	mSkySprite.setTextureRect(sf::IntRect(0, 0, 1600, 1200));
	mSkySprite.setTexture(mSky);
	mSkySprite.setPosition(0, 0);

	mFontTest.loadFromFile("../../../res/Gobold Regular.otf");

	mScore.setFont(mFontTest);
	mScore.setCharacterSize(36);
	mScore.setFillColor(sf::Color::White);

	mScore.setPosition(1300, 400);

	numbLives = playerController->GetLives();

	lifeText.loadFromFile("../../../res/life.png");
	lifeText.setRepeated(true);

	lives.setTextureRect(sf::IntRect(0, 0, 32, 32));
	lives.setTexture(lifeText);
	lives.setScale(sf::Vector2f(1.5, 1.5));
	lives.setPosition(1300, 650);

	mDropTexture.loadFromFile("..\\..\\..\\res\\powerbox.png");
}

void Stage::AddToEntities(Bullet* entity)
{
	entity->SetGameRectBig(false);

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

void Stage::AddToEntities(Enemy* entity)
{
	entities.push_back(entity);
	mEnemies.push_back(entity);
}

void Stage::AddToEntities(Drop* entity)
{
	entities.push_back(entity);
	mEnemyDrops.push_back(entity);
}

void Stage::AddToEntities(Entity* entity)
{
	entities.push_back(entity);
}

void Stage::ResetTimer()
{
	mStageTimer.restart();
}

void Stage::ResetScene()
{
	entities.clear();

	mEnemyBullets.clear();
	mPlayerBullets.clear();
	mEnemies.clear();
	ResetTimer();
}

void Stage::Draw()
{
	mCurrentWindow->setView(mScoreView);

	mCurrentWindow->draw(mSkySprite);

	mCurrentWindow->draw(mScore);

	mCurrentWindow->draw(lives);

	mCurrentWindow->setView(mGameView);

	Scene::Draw();
}

void Stage::Update(float deltaTime)
{
	numbLives = mPlayerController->GetLives();
	lives.setTextureRect(sf::IntRect(0, 0, 32 * numbLives, 32));

	mScoreText = std::to_string(mGameManager->GetScore());
	mScore.setString(mScoreText);

	Scene::Update(deltaTime);
}

void Stage::PlayStage(float deltaTime)
{
	// Player collision with enemy bullets
	Player* activePlayer = mPlayerController->GetActivePlayerPointer();

	if (!mPlayerController->IsInvincible())
	{
		activePlayer->CheckCollisions(&mEnemyBullets);
	}

	// Player collision with drops
	activePlayer->CheckDropCollisions(&mEnemyDrops);

	// Enemy collision with player bullets
	for (int i = 0; i < mEnemies.size(); i++)
	{
		if (!mEnemies[i]->IsEntityActive())
		{
			continue;
		}

		mEnemies[i]->CheckCollisions(&mPlayerBullets);
	}
}

PlayerController* Stage::GetPlayerController()
{
	return mPlayerController;
}
