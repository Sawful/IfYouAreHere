#include "BulletSnake.h"
#include "Character.h"

BulletSnake::BulletSnake(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, sf::Texture* texture, Tag bulletTag, bool isActive, float rotateOffset):
	Bullet(speed, direction, position, rotation, texture, bulletTag, isActive)
{
	mRotateTimer = 0;

	mDamage = damage;

	mBaseDirection = direction;

	mRotationOffset = rotateOffset;

	mHitbox.AddCircle(new sf::CircleShape(8.0f));
}

void BulletSnake::OnHit(Character* other)
{
	other->TakeDamage(mDamage);

	Bullet::OnHit(other);
}

void BulletSnake::Update(float deltaTime)
{
	Bullet::Update(deltaTime);

	mRotateTimer += deltaTime;

	float rotation = tan(sinf(mRotateTimer * 50 + mRotationOffset));
	float rotationStrength = 0.6f;

	mDirection = (sf::Vector2f(rotation, 0.0f) * rotationStrength) + mBaseDirection;
}
