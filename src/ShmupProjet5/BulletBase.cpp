#include "BulletBase.h"
#include "Character.h"
#include <iostream>
#include "Level.h"


std::vector<BulletBase*> BulletBase::mInactiveBullets = std::vector<BulletBase*>();

BulletBase::BulletBase(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, sf::Texture* texture, Tag bulletTag, bool isActive, float bulletSize):
	Bullet(speed, direction, position, rotation, texture, bulletTag, isActive)
{
	mDamage = damage;

	mHitbox.AddCircle(new sf::CircleShape(bulletSize));
}

void BulletBase::OnHit(Character* other)
{
	other->TakeDamage(mDamage);

	Bullet::OnHit(other);
}

void BulletBase::SetStats(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, sf::Texture* texture, Tag bulletTag)
{
	mDamage = damage;
	mSpeed = speed;
	mDirection = direction;
	setPosition(position);
	setRotation(rotation);
	mTexture = texture;

	mSprite = sf::Sprite();
	mSprite.setTexture(*mTexture);

	mSprite.setScale(sf::Vector2f(1.5f, 1.5f));
	mSprite.setOrigin(sf::Vector2f(mSprite.getLocalBounds().width / 2, mSprite.getLocalBounds().height / 2));

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

void BulletBase::RemoveBullet()
{
	SetEntityActive(false);
	mInactiveBullets.push_back(this);
}

BulletBase* BulletBase::InstantiateBullet(int damage, float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, sf::Texture* texture, Tag bulletTag, Level* currentStage)
{
	BulletBase* newBullet;
	if (mInactiveBullets.size() > 0)
	{
		newBullet = mInactiveBullets.back();

		newBullet->SetStats(damage, speed, direction, position, rotation, texture, bulletTag);
		newBullet->SetEntityActive(true);
		mInactiveBullets.pop_back();

		return newBullet;
	}

	newBullet = new BulletBase(damage, speed, direction, position, rotation, texture, bulletTag, true, 8.0f);
	currentStage->AddToEntities(newBullet);
	return newBullet;
}
