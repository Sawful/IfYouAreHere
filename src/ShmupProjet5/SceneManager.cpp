#include "SceneManager.h"
#include "Stage1.h"
#include "Stage2.h"
#include "ExtraStage.h"

SceneManager::SceneManager(sf::RenderWindow* window, GameManager* gm): mMainMenu(window, this), leaderboardMenu(window)
{
	mainWindow = window;
	mGameManager = gm;
}

void SceneManager::Initialize()
{
	mMainMenu.Initialize();
	leaderboardMenu.Initialize();

	mPlayerController = new PlayerController(LIGHT_KITTY_TEXTURE, mGameManager);

	mOverlayAlpha = 0;

	mSceneSwapOverlay = new sf::RectangleShape();
	mSceneSwapOverlay->setPosition(sf::Vector2f(-400, -400));
	mSceneSwapOverlay->setSize(sf::Vector2f(2400, 2400));
	mSceneSwapOverlay->setFillColor(sf::Color(0, 0, 0, 0));

#if defined(_DEBUG)
	Stage2* stage2 = new Stage2(mainWindow, mPlayerController, mGameManager);
	ChangeScene(stage2);
#else
	ChangeScene(&mMainMenu);
#endif

	AddLevel(new Stage1(mainWindow, mPlayerController, mGameManager));

	mExtraStage = new ExtraStage(mainWindow, mPlayerController, mGameManager);

	AddLevel(mExtraStage);
}

void SceneManager::Update()
{
	float dt = mGameManager->GetDeltaTime();

	mCurrentScene->Update(dt);
	UpdateSceneTransition(dt);
}

void SceneManager::Draw()
{
	mCurrentScene->Draw();
	mainWindow->draw(*mSceneSwapOverlay);
}

PlayerController* SceneManager::GetPlayerController()
{
	return mPlayerController;
}

void SceneManager::AddLevel(Stage* newStage)
{
	stages.push_back(newStage);
}

void SceneManager::ChangeScene(Stage* newStage)
{
	if(mCurrentScene != nullptr)
	{
		mCurrentScene->ResetScene();
	}

	mCurrentScene = newStage;
	mCurrentStage = newStage;

	newStage->EnterScene();

	mPlayerController->ChangeStage();
}

void SceneManager::ChangeScene(Scene* newScene)
{
	if (mCurrentScene != nullptr)
	{
		mCurrentScene->ResetScene();
	}

	mCurrentScene = newScene;
	mCurrentStage = nullptr;

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
	SetNextScene(&mMainMenu);
	//ChangeScene(&mainMenu);
}

void SceneManager::ChangeToLeaderboard()
{
	SetNextScene(&leaderboardMenu);
	//ChangeScene(&leaderboardMenu);
}

void SceneManager::SetNextScene(Stage* nextScene)
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
	return mCurrentScene;
}

Stage* SceneManager::GetCurrentStage()
{
	return mCurrentStage;
}

std::vector<Stage*> SceneManager::GetStages()
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

void SceneManager::ShakeExtraStage(float duration)
{
	mExtraStage->SetShake(duration);
}

void SceneManager::UnzoomExtraStage()
{
	mExtraStage->SetExtraBossUnzoom();
}
