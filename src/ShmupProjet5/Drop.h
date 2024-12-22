#pragma once
#include "Hitbox.h"
#include "Entity.h"

class Player;

class Drop : public Entity
{
	// Only if score goes up on collect
	//int mScore;
	// 
	// Only if some boxes grant more than others
	int mWeaponUp = 1;

	sf::Vector2f mDirectionVector;

	Hitbox mHitbox;
	sf::CircleShape mCircleShape;
	float mFallMaxSpeed = 150.0f;
	float mAccelerationFactor = -3.0f;

	float mLifetime;

public:
	Drop(sf::Vector2f position , float lifetime, sf::Texture* texture);

	virtual void Update(float deltaTime);

	Hitbox* GetHitboxPointer();
	void OnCollect(Player* other);
};

