#pragma once
#include "SFML/Graphics.hpp"

class SceneManager;
class SoundManager;
class ResourceManager;
class PlayerController;

class GameManager
{
protected:

	static GameManager* mInstance;
	sf::RenderWindow* mWindow;

	SceneManager* mSceneManager;
	SoundManager* mSoundManager;
	ResourceManager* mResourceManager;

	PlayerController* mPlayerController;

	bool mCinematicPause;
	sf::Clock mPauseTimer;
	float mHitstopTime = 0.25f;

	float mDeltaTime;

	GameManager();
	int mCurrentScore;

	void Update();
	void ProcessEvents();
	void Draw();

public:
	static GameManager* GetInstance();
	void Initialize();
	void Run();

	SceneManager* GetSceneManager();
	SoundManager* GetSoundManager();
	ResourceManager* GetResourceManager();
	sf::RenderWindow* GetWindow();
	bool GetPause();
	void SetPause(bool pause);
	bool HasPauseTimeEnded();
	float GetDeltaTime();
	
	void RaiseScore(int points);
	int GetScore();
	void ResetScore();
};

