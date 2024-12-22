#include "SceneManager.h"
#include "Stage1.h"
#include "Stage2.h"

SceneManager::SceneManager(sf::RenderWindow* window, GameManager* gm): mainMenu(window, this), leaderboardMenu(window)
{
	mainWindow = window;
	mGameManager = gm;

	ChangeScene(&mainMenu);

	sf::Texture pcTexture;
	pcTexture.loadFromFile("..\\..\\..\\res\\BulletTest.png");

	mPlayerController = new PlayerController(&pcTexture, mGameManager);

	mOverlayAlpha = 0;

	mSceneSwapOverlay = new sf::RectangleShape();
	mSceneSwapOverlay->setPosition(sf::Vector2f(-400, -400));
	mSceneSwapOverlay->setSize(sf::Vector2f(2400, 2400));
	mSceneSwapOverlay->setFillColor(sf::Color(0, 0, 0, 0));

	mStage2 = new Stage2(window, mPlayerController, mGameManager);
	AddLevel(new Stage1(window, mPlayerController, mGameManager));
	AddLevel(mStage2);
}

PlayerController* SceneManager::GetPlayerController()
{
	return mPlayerController;
}

void SceneManager::AddLevel(Level* newStage)
{
	newStage->SetOverlay(mSceneSwapOverlay);
	stages.push_back(newStage);
}

void SceneManager::ChangeScene(Level* newStage)
{
	currentScene->ResetScene();

	currentScene = newStage;
	currentStage = newStage;

	newStage->EnterScene();

	mPlayerController->ChangeStage();
}

void SceneManager::ChangeScene(Scene* newScene)
{
	if (currentScene != nullptr)
	{
		currentScene->ResetScene();
	}

	currentScene = newScene;
	currentStage = nullptr;

	newScene->EnterScene();
}

void SceneManager::ChangeToStage(int stage)
{
	stages[stage]->ResetTimer();
	SetNextScene(stages[stage]);
	//ChangeScene(stages[stage]);
}

void SceneManager::ChangeToMainMenu()
{
	SetNextScene(&mainMenu);
	//ChangeScene(&mainMenu);
}

void SceneManager::ChangeToLeaderboard()
{
	SetNextScene(&leaderboardMenu);
	//ChangeScene(&leaderboardMenu);
}

void SceneManager::SetNextScene(Level* nextScene)
{
	if (mNextScene != nullptr)
	{
		return;
	}

	mPlayerController->SetInvincible();
	mExitTime = 1;
	mNextScene = nextScene;
	mNextLevel = nextScene;
}

void SceneManager::SetNextScene(Scene* nextScene)
{
	if (mNextScene != nullptr)
	{
		return;
	}

	mPlayerController->SetInvincible();
	mExitTime = 1;
	mNextScene = nextScene;
	mNextLevel = nullptr;
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}

Level* SceneManager::GetCurrentStage()
{
	return currentStage;
}

std::vector<Level*> SceneManager::GetStages()
{
	return stages;
}

void SceneManager::UpdateSceneTransition(float dt)
{
	mExitTime -= dt;
	if (mNextScene == nullptr)
	{
		mOverlayAlpha = std::lerp(mOverlayAlpha, 0, 2 * dt);

		mSceneSwapOverlay->setFillColor(sf::Color(0, 0, 0, mOverlayAlpha));

		return;
	}

	mOverlayAlpha = std::lerp(mOverlayAlpha, 255, 2 * dt);

	mSceneSwapOverlay->setFillColor(sf::Color(0, 0, 0, mOverlayAlpha));

	if (mExitTime > 0.0f)
	{
		return;
	}

	if (mNextLevel != nullptr)
	{
		ChangeScene(mNextLevel);
	}
	else
	{
		ChangeScene(mNextScene);
	}

	mNextScene = nullptr;
	mNextLevel = nullptr;
}

sf::RectangleShape* SceneManager::GetSceneOverlay()
{
	return mSceneSwapOverlay;
}

void SceneManager::ShakeStage2(float duration)
{
	mStage2->SetShake(duration);
}

void SceneManager::UnzoomStage2()
{
	mStage2->SetBoss2Unzoom();
}