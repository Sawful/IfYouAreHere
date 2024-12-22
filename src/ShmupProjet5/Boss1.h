#pragma once
#include "Enemy.h"

enum Boss1States
{
	Arriving,
	Phase1,
	Phase2,
	Phase3,
	Phase4
};

class BulletSpawner;
class BulletSpawnerBoss11Main;
class BulletSpawnerBoss11Sub;
class BulletSpawnerBoss12;
class BulletSpawnerBoss13;
class BulletSpawnerBoss14;
struct Path;

class Boss1 : public Enemy
{
	BulletSpawnerBoss11Main* mBulletSpawnerState1Main;
	BulletSpawnerBoss11Sub* mBulletSpawnerState1Sub;
	BulletSpawnerBoss12* mBulletSpawnerState2;
	BulletSpawnerBoss13* mBulletSpawnerState3;
	BulletSpawnerBoss14* mBulletSpawnerState4;

	Boss1States mCurrentState;

	Path* mRecenterPath;

	std::vector<Path*> mMovementPathArriving;
	std::vector<Path*> mMovementPathState1;
	std::vector<Path*> mMovementPathState2;
	std::vector<Path*> mMovementPathState3;
	std::vector<Path*> mMovementPathState4;

	std::vector < BulletSpawner*> mCurrentBulletSpawners;
	std::vector<Path*>* mCurrentMovementPath;

public:
	Boss1(sf::Vector2f position, float rotation, bool isActive, TextureName texture);

	virtual void Update(float deltaTime);
	virtual void Attack();
	virtual void Move(float deltaTime);
	virtual void Die() override;
	virtual void TakeDamage(int damage) override;
};

