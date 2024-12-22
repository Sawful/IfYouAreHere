#include "EnemyTest.h"


EnemyTest::EnemyTest(sf::Vector2f position, float rotation, bool isActive, TextureName texture):
	Enemy(position, rotation, 40, texture, isActive)
{
	mBulletSpawnerPTR = new BulletSpawnerTest(this);

	mSprite.setOrigin(sf::Vector2f(130.0f, 97.0f));

	timeAlive.restart();
	mDirection = sf::Vector2f(1.0f, 0.0f);
	mSpeed = 100.0f;
	mHealth = 20;

	mHitbox.AddCircle(new sf::CircleShape(110.0f));

	scoreValue = 5;
}

void EnemyTest::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(mSprite, states);
}


void EnemyTest::Update(float deltaTime)
{
	mDirection.x = 1 - sinf(timeAlive.getElapsedTime().asSeconds());
	mDirection.y = sinf(timeAlive.getElapsedTime().asSeconds());

	//Normalize direction vector
	float len = sqrt(mDirection.x * mDirection.x + mDirection.y * mDirection.y);
	if (len != 0) {
		mDirection.x = mDirection.x / len;
		mDirection.y = mDirection.y / len;
	}

	mBulletSpawnerPTR->Update(deltaTime);
	Move(deltaTime);
}

