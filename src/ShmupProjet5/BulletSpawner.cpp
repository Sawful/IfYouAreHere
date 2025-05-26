#include "BulletSpawner.h"
#include "GameManager.h"
#include "SceneManager.h"

sf::Vector2f* RotateV2f(sf::Vector2f v, float delta) {
	return new sf::Vector2f(
		v.x * cosf(delta) - v.y * sinf(delta),
		v.x * sinf(delta) + v.y * cosf(delta)
	);
}

//Normalize direction vector
sf::Vector2f* NormalizeV2f(sf::Vector2f v)
{
	float len = sqrt(v.x * v.x + v.y * v.y);
	if (len != 0) 
	{
		return new sf::Vector2f(v.x / len, v.y / len);
	}
	
	return new sf::Vector2f(v.x, v.y);
}


BulletSpawner::BulletSpawner()
{
	
}

void BulletSpawner::SetCurrentStage(Stage* currentStage)
{
	mCurrentStage = currentStage;
}

void BulletSpawner::RemoveBullets()
{
	for (int i = 0; i < mBullets.size(); i++)
	{
		mBullets[i]->SetEntityActive(false);
	}

	mBullets.clear();
}

void BulletSpawner::Reset()
{
}
