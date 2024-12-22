#pragma once
#include "SFML/Graphics.hpp"

class SceneManager;
class SoundManager;

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

	GameManager();
	int currentScore;

public:
	static GameManager* GetInstance();
	SceneManager* GetSceneManager();
	SoundManager* GetSoundManager();
	sf::RenderWindow* GetWindow();
	bool GetPause();
	void SetPause(bool pause);
	bool HasPauseTimeEnded();
	
	void RaiseScore(int points);
	int GetScore();
};

