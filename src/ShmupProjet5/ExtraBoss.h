#pragma once
#include "Enemy.h"
#include "BulletSpawner.h"
#include "BulletSpawnerExtraBoss.h"

enum ExtraBossStates
{
	Waiting, // Waits like 5 seconds at the center of the screen (he's already there on ExtraStage transition)
	Phase1,
	Phase2 // Satori spin circle + screen shake and unzoom
};

struct ExtraBossPattern
{
	std::vector<Path*> patternPath;
	std::vector <BulletSpawner*> patternSpawners;
};

class ExtraBoss : public Enemy
{
	int mPathNumber;

	ExtraBossPattern mPatternWaiting;
	ExtraBossPattern mPattern1;
	ExtraBossPattern mPattern2;
	ExtraBossPattern mPattern3;
	ExtraBossPattern mPattern4;
	ExtraBossPattern mPattern5;

	ExtraBossStates mState;

	BulletSpawnerExtraBossPhase1Perma* mPermaSpawner;
	float mPermaShotTime = 25.94f;
	float mPermaShotCooldown = 0.405405f;
	float mPermaShotHighest = 0;
	sf::Clock mPermaClock;

	float mFaceChangeTimeWaiting = 0.0f;
	float mFaceChangeCooldownWaiting = 0.5f;

	float mFaceChangeTimeP2 = 0.0f;
	float mFaceChangeCooldownP2 = 0.03f;

	std::vector < ExtraBossPattern*> mPhase1Patterns;

	sf::RectangleShape* mPreviewRectangle;
	sf::Sprite* mLaser;
	sf::Texture mLaserTexture;

	ExtraBossPattern* mCurrentPattern;

public:
	ExtraBoss(sf::Vector2f position, float rotation, bool isActive, TextureName texture);

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

