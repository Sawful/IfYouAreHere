#pragma once
#include "Bullet.h"
#include "Scene.h"
#include "Level.h"
#include "ctime"
#include "SFML/Graphics.hpp"

sf::Vector2f* RotateV2f(sf::Vector2f v, float delta);
sf::Vector2f* NormalizeV2f(sf::Vector2f v);

class BulletSpawner: public sf::Transformable
{
protected:
	Level* mCurrentStage;
	std::vector<Bullet*> mBullets;

public:
	BulletSpawner();
	void SetCurrentStage(Level* currentStage);
	void RemoveBullets();
	virtual void Update(float dt) = 0;
	virtual void Reset();
};

