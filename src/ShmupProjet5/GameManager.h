#pragma once
#include "SFML/Graphics.hpp"

class SceneManager;
class SoundManager;
class ResourceManager;

class GameManager
{
protected:

	static GameManager* mInstance;
	sf::RenderWindow* mWindow;

	bool mCinematicPause;
	sf::Clock mPauseTimer;
	float mHitstopTime = 0.25f;

	SceneManager* mSceneManager;
	SoundManager* mSoundManager;
	ResourceManager* mResourceManager;

	GameManager();
	int mCurrentScore;

public:
	static GameManager* GetInstance();
	void Initialize();
	SceneManager* GetSceneManager();
	SoundManager* GetSoundManager();
	ResourceManager* GetResourceManager();
	sf::RenderWindow* GetWindow();
	bool GetPause();
	void SetPause(bool pause);
	bool HasPauseTimeEnded();
	
	void RaiseScore(int points);
	int GetScore();
	void ResetScore();
};

