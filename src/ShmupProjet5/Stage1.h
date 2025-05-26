#pragma once
#include "Stage.h"
#include "EnemyTest.h"
#include "Path.h"


class Stage1: public Stage
{
	sf::Texture mShotSlugTexture;
	sf::Texture mCircleGuyTexture;
	sf::Texture mTripleShotTexture;
	sf::Texture mBossTexture;

	sf::Texture mForest;

	sf::Sprite mBackground1;
	sf::Sprite mBackground2;

	float mTimeUntilNextWave;
	int mWave;

public:
	Stage1(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm);
	virtual void Update(float deltaTime) override;

	void SpawnWave(int wave);

	virtual void PlayStage(float deltaTime) override;
	virtual void ResetScene() override;

	virtual void Draw() override; 
	virtual void EnterScene();
};

