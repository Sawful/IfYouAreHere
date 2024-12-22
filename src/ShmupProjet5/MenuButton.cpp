#include "MenuButton.h"


MenuButton::MenuButton(sf::Vector2f position, float rotation, sf::Vector2f size, TextureName texture, TextureName textureHovered): Entity(position, rotation, texture, true)
{
	mRectangle = sf::RectangleShape(size);

	mTexture = GameManager::GetInstance()->GetResourceManager()->GetTexture(texture);
	mTextureHovered = GameManager::GetInstance()->GetResourceManager()->GetTexture(textureHovered);

	mIsHovered = false;

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
	}

	else
	{
		mRectangle.setTexture(mTexture);
	}
}

void MenuButton::Update(float deltaTime)
{
}
