#pragma once
#include "Level.h"
#include "EnemyTest.h"
#include "Path.h"


class Stage2 : public Level
{
	sf::Texture mBossTexture;

	float mTimeUntilNextWave;
	int mWave;

	sf::Texture mSpace;

	std::vector<sf::Vector2f*> mShakeVectors;
	int mShakeVectorIndex = 0;

	float mShakeTime;
	float mShakeCooldown = 0.05f;
	float mShakeDuration;
	bool mIsShaking;

	bool mIsUnzooming = false;
	bool mIsUnzoomingInitial = false;

	sf::Sprite mBackground1;
	sf::Sprite mBackground2;

public:
	Stage2(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm);
	virtual void Update(float deltaTime) override;
	void SpawnWave(int wave);
	virtual void AddToEntities(Bullet* entity);
	virtual void AddToEntities(Enemy* entity);
	virtual void AddToEntities(Drop* entity);

	virtual void AddToEntities(Entity* entity);
	virtual void PlayLevel(float deltaTime) override;
	virtual void ResetScene() override;
	virtual void Draw() override;
	virtual void EnterScene();
	void SetShake(float duration);
	void SetBoss2Unzoom();
};

