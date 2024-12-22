#pragma once
#include "Bullet.h"

class BulletAccelerate : public Bullet
{
	int mDamage;
	float mMaxSpeed;
	float mAccelerationFactor;

public:
	BulletAccelerate(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, sf::Texture* texture, Tag bulletTag, bool isActive, float maxSpeed, float accelerationFactor);
	virtual void OnHit(Character* other) override;
	virtual void Update(float deltaTime) override;
};

