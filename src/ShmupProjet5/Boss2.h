#pragma once
#include "Enemy.h"
#include "BulletSpawner.h"
#include "BulletSpawnerBoss2.h"

enum Boss2States
{
	Waiting, // Waits like 5 seconds at the center of the screen (he's already there on Stage2 transition)
	Phase1,
	Phase2 // Satori spin circle + screen shake and unzoom
};

struct Boss2Pattern
{
	std::vector<Path*> patternPath;
	std::vector <BulletSpawner*> patternSpawners;
};

class Boss2 : public Enemy
{
	int mPathNumber;

	Boss2Pattern mPatternWaiting;
	Boss2Pattern mPattern1;
	Boss2Pattern mPattern2;
	Boss2Pattern mPattern3;
	Boss2Pattern mPattern4;
	Boss2Pattern mPattern5;

	Boss2States mState;

	BulletSpawnerBoss2Phase1Perma* mPermaSpawner;
	float mPermaShotTime = 25.94f;
	float mPermaShotCooldown = 0.405405f;
	float mPermaShotHighest = 0;
	sf::Clock mPermaClock;

	float mFaceChangeTimeWaiting = 0.0f;
	float mFaceChangeCooldownWaiting = 0.5f;

	float mFaceChangeTimeP2 = 0.0f;
	float mFaceChangeCooldownP2 = 0.03f;

	std::vector < Boss2Pattern*> mPhase1Patterns;

	sf::RectangleShape* mPreviewRectangle;
	sf::Sprite* mLaser;
	sf::Texture mLaserTexture;

	Boss2Pattern* mCurrentPattern;

public:
	Boss2(sf::Vector2f position, float rotation, bool isActive, sf::Texture* texture, sf::Texture* dropTexture);

	virtual void Update(float deltaTime);
	virtual void Attack();
	virtual void Move(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void Die() override;
	virtual void TakeDamage(int damage) override;
	virtual void SetPreviewRectangle(bool display, sf::Vector2f position, float rotation);
	virtual void SetPreviewRectangle(bool display);
	void DisplayLaser(bool display, sf::Vector2f position, float rotation);
	void DisplayLaser(bool display);
};

