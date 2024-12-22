#pragma once
#include "Hitbox.h"
#include "Entity.h"

class Character;

enum OwnerType
{
	PLAYER,
	ENEMY
};

class Bullet: public Entity
{
protected:
	OwnerType mOwnerType;
	int mDamage;
	std::vector<sf::CircleShape> mCircleShapes;
	Hitbox mHitbox;
	sf::Vector2f mDirection;
	float mSpeed;

	sf::FloatRect mGameRect;
	
public:
	Bullet(float speed, sf::Vector2f direction, sf::Vector2f position, float rotation, TextureName texture, Tag bulletTag, bool isActive);
	void Reset(float speed, sf::Vector2f direction, sf::Vector2f position, float rotation);
	virtual void Update(float deltaTime);
	virtual void RemoveBullet();
	Hitbox* GetHitboxPointer();
	OwnerType GetOwnerType();
	virtual void OnHit(Character* other);
	void Destroy();
	sf::Vector2f GetDirection();
	void SetDirection(sf::Vector2f newDirection);
	float GetSpeed();
	void SetSpeed(float newSpeed);

	void SetTransparency(int alpha);

	void SetGameRectBig(bool isBig);
	
	//virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

