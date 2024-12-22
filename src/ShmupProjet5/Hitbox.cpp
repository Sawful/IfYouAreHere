#include "Hitbox.h"
#include "cmath"
#include <iostream>

Hitbox::Hitbox(Tag hitboxTag)
{
	mHitboxTag = hitboxTag;
}

std::vector<sf::CircleShape> Hitbox::GetCollisionCircles()
{
	return mCircles;
}

bool Hitbox::IsColliding(Hitbox* other)
{
	std::vector<sf::CircleShape> otherCollisionCircles = other->GetCollisionCircles();

	float distance;

	for (sf::CircleShape collisionCircle : mCircles)
	{
		for (sf::CircleShape otherCollisionCircle : otherCollisionCircles)
		{
			//std::cout << otherCollisionCircle.getPosition().x << ", " << otherCollisionCircle.getPosition().y;

			sf::Vector2f difference = collisionCircle.getGlobalBounds().getPosition() - otherCollisionCircle.getGlobalBounds().getPosition();
			distance = sqrt(difference.x * difference.x + difference.y * difference.y);

			if (distance <= collisionCircle.getRadius() + otherCollisionCircle.getRadius())
			{
				return true;
			}
		}
	}

	return false;
}

void Hitbox::AddCircle(sf::CircleShape* circle)
{
	mCircles.push_back(*circle);
}

void Hitbox::SetPosition(sf::Vector2f position)
{
	// Find a way to add offset to different circles
	for (int i = 0; i < mCircles.size(); i++)
	{
		mCircles[i].setPosition(position);
	}
}

