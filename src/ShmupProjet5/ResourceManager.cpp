#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
	mDinoKittyLight.loadFromFile("..\\..\\..\\res\\lightkitty_all.png");
	mDinoKittyDark.loadFromFile("..\\..\\..\\res\\darkkitty_all.png");
}

ResourceManager::~ResourceManager()
{
}

sf::Texture* ResourceManager::GetTexture(TextureName texture)
{
	switch (texture)
	{
	case LIGHT_KITTY:
		return &mDinoKittyLight;

	case DARK_KITTY:
		return &mDinoKittyDark;
	}

	return nullptr;
}
