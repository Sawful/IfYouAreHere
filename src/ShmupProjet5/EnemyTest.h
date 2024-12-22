#pragma once
#include "BulletSpawnerTest.h"
#include "Enemy.h"

class EnemyTest: public Enemy
{
	sf::Texture* mTexture;
	
	BulletSpawner* mBulletSpawnerPTR;

	sf::Clock timeAlive;

public:
	EnemyTest(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void Update(float deltaTime);
};

