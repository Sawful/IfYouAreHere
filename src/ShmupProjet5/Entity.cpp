#include "Entity.h"


Entity::Entity(sf::Vector2f position, float rotation, sf::Texture* texture, bool isActive)
{
	mIsActive = isActive;

	setPosition(position);
	setRotation(rotation);
	mTexture = texture;

	mSprite.setTexture(*mTexture);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(mSprite, states);
}

void Entity::SetEntityActive(bool active)
{
	mIsActive = active;
}

bool Entity::IsEntityActive()
{
	return mIsActive;
}
