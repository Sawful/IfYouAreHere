#include "Bullet.h"
#include "Character.h"
#include <iostream>


Bullet::Bullet(float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, sf::Texture* texture, Tag bulletTag, bool isActive) :
	Entity(position, rotation, texture, isActive), mHitbox(bulletTag)
{
	mSpeed = speed;
	mDirection = direction;
	setPosition(position);
	setRotation(rotation);

	mSprite.setScale(sf::Vector2f(1.5f, 1.5f));
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));

	mGameRect = sf::FloatRect(sf::Vector2f(-mSprite.getLocalBounds().width / 2 * 1.5f, -mSprite.getLocalBounds().height / 2 * 1.5f),
		sf::Vector2f(800.0f + mSprite.getLocalBounds().width * 1.5f, 800.0f + mSprite.getLocalBounds().height * 1.5f));

	if (bulletTag == PLAYERBULLET)
	{
		mOwnerType = PLAYER;
	}
	else if (bulletTag == ENEMYBULLET)
	{
		mOwnerType = ENEMY;
	}
	else
	{
		std::cout << "Cannot get owner type. (invalid bullet type)";
	}
}

void Bullet::Reset(float speed, sf::Vector2f direction, sf::Vector2f position, float rotation)
{
	mSpeed = speed;
	mDirection = direction;
	setPosition(position);
	setRotation(rotation);
}

void Bullet::Update(float deltaTime)
{
	if (getPosition().x < mGameRect.left ||
		getPosition().x > mGameRect.width + mGameRect.left ||
		getPosition().y < mGameRect.top ||
		getPosition().y > mGameRect.height + mGameRect.top)

	{
		RemoveBullet();
	}

	// Typical bullet behavior, going somewhere
	move(deltaTime * mSpeed * mDirection);
	mHitbox.SetPosition(getPosition());
}

void Bullet::RemoveBullet()
{
	SetEntityActive(false);
}

Hitbox* Bullet::GetHitboxPointer()
{
	return &mHitbox;
}

OwnerType Bullet::GetOwnerType()
{
	return mOwnerType;
}

void Bullet::OnHit(Character* other)
{
	Destroy();
}

void Bullet::Destroy()
{
	mIsActive = false;
}

sf::Vector2f Bullet::GetDirection()
{
	return mDirection;
}

void Bullet::SetDirection(sf::Vector2f newDirection)
{
	mDirection = newDirection;
}

float Bullet::GetSpeed()
{
	return mSpeed;
}

void Bullet::SetSpeed(float newSpeed)
{
	mSpeed = newSpeed;
}

void Bullet::SetTransparency(int alpha)
{
	mSprite.setColor(sf::Color(mSprite.getColor().r, mSprite.getColor().g, mSprite.getColor().b, alpha));
}

void Bullet::SetGameRectBig(bool isBig)
{
	if (isBig)
	{
		mGameRect = sf::FloatRect(sf::Vector2f(-200.0f -mSprite.getLocalBounds().width / 2 * 1.5f, -200.0f -mSprite.getLocalBounds().height / 2 * 1.5f),
			sf::Vector2f(1200.0f + mSprite.getLocalBounds().width * 1.5f, 1200.0f + mSprite.getLocalBounds().height * 1.5f));
	}

	else
	{
		mGameRect = sf::FloatRect(sf::Vector2f(-mSprite.getLocalBounds().width / 2 * 1.5f, -mSprite.getLocalBounds().height / 2 * 1.5f),
			sf::Vector2f(800.0f + mSprite.getLocalBounds().width * 1.5f, 800.0f + mSprite.getLocalBounds().height * 1.5f));
	}
}
