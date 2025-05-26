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
	GameManager* mGameManager;
	PlayerController* mPlayerController;

	sf::RectangleShape* mSceneSwapOverlay;
	float mOverlayAlpha;
	float mExitTime;
	Scene* mNextScene;
	Stage* mNextLevel;

	std::vector<Stage*> stages;
	ExtraStage* mExtraStage;
	
	Menu mMainMenu;
	LeaderboardMenu leaderboardMenu;

	Scene* mCurrentScene;
	Stage* mCurrentStage;

	void Initialize();
	void Update();
	void Draw();

public:
	SceneManager(sf::RenderWindow* window, GameManager* gm);

	PlayerController* GetPlayerController();
	void AddLevel(Stage* newStage);
	void ChangeScene(Stage* newStage);
	void ChangeScene(Scene* newScene);
	void ChangeToStage(int stage);
	void ChangeToMainMenu();
	void ChangeToLeaderboard();
	void SetNextScene(Stage* nextScene);
	void SetNextScene(Scene* nextScene);
	Scene* GetCurrentScene();
	Stage* GetCurrentStage();
	std::vector<Stage*> GetStages();
	void UpdateSceneTransition(float dt);
	sf::RectangleShape* GetSceneOverlay();
	void ShakeExtraStage(float duration);
	void UnzoomExtraStage();

	friend class GameManager;
};

