#pragma once
#include "Entity.h"
#include "Hitbox.h"

class Bullet;
class Drop;

class Character: public Entity
{
protected:
	Hitbox mHitbox;

public:
	Character(sf::Vector2f position, float rotation, sf::Texture* texture, Tag hitboxTag, bool isActive);
	virtual void CheckCollisions(std::vector<Bullet*>* bullets);
	//virtual void Move(float deltaTime) = 0;
	virtual void TakeDamage(int damage) = 0;
	virtual void Die() = 0;
};

