#pragma once
#include "Stage1.h"
#include "ExtraStage.h"
#include "Menu.h"
#include "LeaderboardMenu.h"


enum sceneState
{
	STAGE, MENU
};

class SceneManager
{
	sf::RenderWindow* mainWindow;

	sf::RectangleShape* mSceneSwapOverlay;
	float mOverlayAlpha;
	float mExitTime;
	Scene* mNextScene;
	Level* mNextLevel;

	std::vector<Level*> stages;
	ExtraStage* mExtraStage;
	
	Menu mMainMenu;
	LeaderboardMenu leaderboardMenu;

	Scene* mCurrentScene;
	Level* mCurrentStage;

	GameManager* mGameManager;
	PlayerController* mPlayerController;

	void Initialize();
	void Update();
	void Draw();

public:
	SceneManager(sf::RenderWindow* window, GameManager* gm);

	PlayerController* GetPlayerController();
	void AddLevel(Level* newStage);
	void ChangeScene(Level* newStage);
	void ChangeScene(Scene* newScene);
	void ChangeToStage(int stage);
	void ChangeToMainMenu();
	void ChangeToLeaderboard();
	void SetNextScene(Level* nextScene);
	void SetNextScene(Scene* nextScene);
	Scene* GetCurrentScene();
	Level* GetCurrentStage();
	std::vector<Level*> GetStages();
	void UpdateSceneTransition(float dt);
	sf::RectangleShape* GetSceneOverlay();
	void ShakeExtraStage(float duration);
	void UnzoomExtraStage();

	friend class GameManager;
};

