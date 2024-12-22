#include "GameManager.h"
#include "SceneManager.h"
#include "SoundManager.h"


GameManager* GameManager::mInstance = nullptr;

GameManager::GameManager(): mWindow(new sf::RenderWindow(sf::VideoMode(1200, 900), "If you are here", sf::Style::Titlebar | sf::Style::Close)),
mSoundManager(new SoundManager()),
mSceneManager(new SceneManager(mWindow, this))
{
	mSceneManager->GetCurrentScene();
	mCurrentScore = 0;
}

GameManager* GameManager::GetInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new GameManager();
	}
	return mInstance;
}

SceneManager* GameManager::GetSceneManager()
{
	return mSceneManager;
}

SoundManager* GameManager::GetSoundManager()
{
	return mSoundManager;
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

