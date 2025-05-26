#pragma once
#include "Bullet.h"
#include "Scene.h"
#include "Stage.h"
#include "ctime"
#include "SFML/Graphics.hpp"

sf::Vector2f* RotateV2f(sf::Vector2f v, float delta);
sf::Vector2f* NormalizeV2f(sf::Vector2f v);

class BulletSpawner: public sf::Transformable
{
protected:
	Stage* mCurrentStage;
	std::vector<Bullet*> mBullets;

public:
	BulletSpawner();
	void SetCurrentStage(Stage* currentStage);
	void RemoveBullets();
	virtual void Update(float dt) = 0;
	virtual void Reset();
};

