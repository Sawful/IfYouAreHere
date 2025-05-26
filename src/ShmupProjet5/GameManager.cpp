#include "GameManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "PlayerController.h"


GameManager* GameManager::mInstance = nullptr;

GameManager::GameManager(): mWindow(new sf::RenderWindow(sf::VideoMode(1200, 900), "If you are here", sf::Style::Titlebar | sf::Style::Close)),
mSoundManager(new SoundManager()),
mResourceManager(new ResourceManager()),
mSceneManager(new SceneManager(mWindow, this)) {}

void GameManager::Update()
{
	mSceneManager->Update();
}

void GameManager::Draw()
{
	mWindow->clear(sf::Color::Black);

	mSceneManager->Draw();

	mWindow->display();
}

void GameManager::ProcessEvents()
{
	sf::Event event;
	while (mWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			delete GetSoundManager();

			mWindow->close();
		}

		if (event.KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				mPlayerController->Swap();
			}
		}
	}
}

GameManager* GameManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new GameManager();
	}
	return mInstance;
}

void GameManager::Initialize()
{
	mSceneManager->Initialize();
	mCurrentScore = 0;
	mPlayerController = mSceneManager->GetPlayerController();
}

void GameManager::Run()
{
	sf::Clock clock;

	while (mWindow->isOpen())
	{
		mDeltaTime = clock.restart().asSeconds();

		if (GetPause())
		{
			// Until unpaused, no logic runs, and nothing is drawn.
			if (HasPauseTimeEnded())
			{
				SetPause(false);
			}
			continue;
		}

		ProcessEvents();
		Update();
		Draw();
	}
}

SceneManager* GameManager::GetSceneManager()
{
	return mSceneManager;
}

SoundManager* GameManager::GetSoundManager()
{
	return mSoundManager;
}

ResourceManager* GameManager::GetResourceManager()
{
	return mResourceManager;
}

sf::RenderWindow* GameManager::GetWindow()
{
	return mWindow;
}

bool GameManager::GetPause()
{
	return mCinematicPause;
}

void GameManager::SetPause(bool pause)
{
	mCinematicPause = pause;

	if(mCinematicPause)
		mPauseTimer.restart();
}

bool GameManager::HasPauseTimeEnded()
{
	return mPauseTimer.getElapsedTime().asSeconds() >= mHitstopTime;
}

float GameManager::GetDeltaTime()
{
	return mDeltaTime;
}

void GameManager::RaiseScore(int points) {
	mCurrentScore += points;
}

int GameManager::GetScore()
{
	return mCurrentScore;
}

void GameManager::ResetScore()
{
	mCurrentScore = 0;
}

