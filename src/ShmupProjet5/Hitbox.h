#pragma once
#include "SFML/Graphics.hpp"
//#include "Entity.h"

enum Tag
{
	PLAYERBULLET,
	ENEMYBULLET,
	ENEMYTAG,
	PLAYERTAG,
	PICKUP
};


class Hitbox
{
protected:
	Tag mHitboxTag;
	std::vector<sf::CircleShape> mCircles;
	std::vector<sf::Vector2f> mOffset;

public:
	Hitbox(Tag hitboxTag);
	std::vector<sf::CircleShape> GetCollisionCircles();
	bool IsColliding(Hitbox* other);
	void AddCircle(sf::CircleShape* circle);
	void SetPosition(sf::Vector2f position);
};

