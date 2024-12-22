#pragma once
#include "SFML/Graphics.hpp"


class Entity : public sf::Drawable, public sf::Transformable
{
protected:
	sf::Texture* mTexture;
	sf::Sprite mSprite;
	bool mIsActive;

public:
	virtual void Update(float deltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void SetEntityActive(bool active);
	bool IsEntityActive();

	Entity(sf::Vector2f position, float rotation, sf::Texture* texture, bool isActive); // initial position, rotation, sprite
};
