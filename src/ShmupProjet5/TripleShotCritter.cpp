#include "TripleShotCritter.h"
#include "GameManager.h"
#include "SceneManager.h"

TripleShotCritter::TripleShotCritter(sf::Vector2f position, float rotation, bool isActive, TextureName texture, std::vector<Path*> movementPath) :
Enemy(position, rotation, 3, texture, isActive)
{
	mMovementPath = movementPath;
	mBulletSpawnerPTR = new BulletSpawnerTriple(this, mCurrentStage);

	mHealth = 100;

	scoreValue = 20;

	mSprite.setOrigin(sf::Vector2f(33.0f, 36.0f));

	mHitbox.AddCircle(new sf::CircleShape(36.0f));
}

void TripleShotCritter::Update(float deltaTime)
{
	mBulletSpawnerPTR->Update(deltaTime);
	Move(deltaTime);
}

// Nothing
void TripleShotCritter::Attack()
{
}
