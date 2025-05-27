#pragma once
#include "Stage.h"
#include "EnemyTest.h"
#include "Path.h"


class Stage1: public Stage
{
	sf::Texture mBackgroundTexture;

	sf::Sprite mBackground1;
	sf::Sprite mBackground2;

public:
	Stage1(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm);
	virtual void Update(float deltaTime) override;

	virtual void SpawnWave(int wave) override;

	virtual void Draw() override; 
	virtual void EnterScene() override;
};

