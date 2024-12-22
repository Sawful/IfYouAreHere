#include "Drop.h"
#include "Player.h"
#include "BulletSpawner.h"
#include "cmath"


Drop::Drop(sf::Vector2f position, float lifetime, sf::Texture* texture) : Entity(position, 0, texture, true), mHitbox(PICKUP)
{
	mHitbox.AddCircle(new sf::CircleShape(32.0f));

	mSprite.setScale(sf::Vector2f(1.5f, 1.5f));
	mSprite.setOrigin(sf::Vector2f(6.0f, 6.0f));

	mLifetime = lifetime;

	mDirectionVector = sf::Vector2f(0.0f, -4.0f);

	float deltaRotation = ((rand() % 32) - 16) / 80.0f;
	float deltaNorm = (rand() % 100) / 200.0f + 0.75f;

	mDirectionVector = *RotateV2f(mDirectionVector, deltaRotation);
	mDirectionVector = deltaNorm * mDirectionVector;
}

void Drop::Update(float deltaTime)
{
	mLifetime -= deltaTime;

	if (mLifetime < 0)
	{
		mIsActive = false;
	}

	move(mDirectionVector * mFallMaxSpeed * deltaTime);

	mHitbox.SetPosition(getPosition());

	mDirectionVector = mDirectionVector * (1.0f - deltaTime) + sf::Vector2f(0.0f, 1.0f) * deltaTime;

	//mAccelerationFactor = std::lerp(mAccelerationFactor, 1.0f, 0.6f * deltaTime);
}

Hitbox* Drop::GetHitboxPointer()
{
	return &mHitbox;
}

void Drop::OnCollect(Player* other)
{
	other->CollectDrop(mWeaponUp);
	mIsActive = false;
}
