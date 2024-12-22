#pragma once
#include "Bullet.h"

class Level;

class BulletBase: public Bullet
{
	int mDamage;
	static std::vector<BulletBase*> mInactiveBullets;

public:
	BulletBase(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, TextureName texture, Tag bulletTag, bool isActive, float bulletSize);
	virtual void OnHit(Character* other) override;

	void SetStats(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, TextureName texture, Tag bulletTag);
	virtual void RemoveBullet();

	static BulletBase* InstantiateBullet(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, TextureName texture, Tag bulletTag, Level* currentStage);
};

