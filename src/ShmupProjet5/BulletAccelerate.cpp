#include "BulletAccelerate.h"
#include "Character.h"

BulletAccelerate::BulletAccelerate(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, TextureName texture, Tag bulletTag, bool isActive, float maxSpeed, float accelerationFactor):
	Bullet(speed, direction, position, rotation, texture, bulletTag, isActive)
{
	mDamage = damage;
	mMaxSpeed = maxSpeed;
	mAccelerationFactor = accelerationFactor;
}

void BulletAccelerate::OnHit(Character* other)
{
	other->TakeDamage(mDamage);

	Bullet::OnHit(other);
}

void BulletAccelerate::Update(float deltaTime)
{
	SetSpeed(std::lerp(mSpeed, mMaxSpeed, mAccelerationFactor * deltaTime));
	Bullet::Update(deltaTime);
}
