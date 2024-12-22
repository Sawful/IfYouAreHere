#include "MenuButton.h"


MenuButton::MenuButton(sf::Vector2f position, float rotation, sf::Vector2f size, sf::Texture* texture, sf::Texture* textureHovered): Entity(position, rotation, texture, true)
{
	mRectangle = sf::RectangleShape(size);

	mTexture = texture;
	mTextureHovered = textureHovered;

	mRectangle.setTexture(mTexture);
}

void MenuButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(mRectangle, states);
}

void MenuButton::SetHover(bool hover)
{
	mIsHovered = hover;

	if (mIsHovered)
	{
		mRectangle.setTexture(mTextureHovered);
		//mRectangle.setRotation(15.0f);
	}

	else
	{
		mRectangle.setTexture(mTexture);
		//mRectangle.setRotation(0.0f);
	}
}

void MenuButton::Update(float deltaTime)
{
	
	
}
