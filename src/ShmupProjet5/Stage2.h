#pragma once
#include "Stage.h"

class Stage2 : public Stage
{
	sf::Texture mBackgroundTexture;

	sf::Sprite mBackground1;
	sf::Sprite mBackground2;


public:
	Stage2(sf::RenderWindow* window, PlayerController* playerController, GameManager* gm);
	virtual void Update(float deltaTime) override;

	void SpawnWave(int wave);

	virtual void Draw() override;
	virtual void EnterScene();
};

