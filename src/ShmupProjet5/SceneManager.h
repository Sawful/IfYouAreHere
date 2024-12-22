#pragma once
#include "Stage1.h"
#include "Stage2.h"
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
	Stage2* mStage2;
	
	Menu mainMenu;
	LeaderboardMenu leaderboardMenu;

	Scene* currentScene;
	Level* currentStage;

	GameManager* mGameManager;
	PlayerController* mPlayerController;

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
	void ShakeStage2(float duration);
	void UnzoomStage2();
};

