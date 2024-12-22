#pragma once
#include "Entity.h"


class MenuButton: public Entity
{
	sf::RectangleShape mRectangle;
	sf::Color mColor;
	bool mIsHovered;

	sf::Texture* mTexture;
	sf::Texture* mTextureHovered;

public:
	MenuButton(sf::Vector2f position, float rotation, sf::Vector2f size, TextureName texture, TextureName textureHovered);
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void SetHover(bool hover);
	virtual void Update(float deltaTime);
};

