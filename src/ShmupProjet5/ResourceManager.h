#pragma once
#include "SFML/Graphics.hpp"


enum TextureName
{
	LIGHT_KITTY,
	DARK_KITTY
};

class ResourceManager
{
	sf::Texture mDinoKittyLight;
	sf::Texture mDinoKittyDark;


public:
	ResourceManager();
	~ResourceManager();

	sf::Texture* GetTexture(TextureName texture);
};

