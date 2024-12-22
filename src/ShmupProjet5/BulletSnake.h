#pragma once
#include "Bullet.h"


class BulletSnake: public Bullet
{
	int mDamage;
	float mRotateTimer;
	float mRotationOffset;
	sf::Vector2f mBaseDirection;

public:
	BulletSnake(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, TextureName texture, Tag bulletTag, bool isActive, float rotateOffset);
	virtual void OnHit(Character* other) override;
	virtual void Update(float deltaTime) override;
};

