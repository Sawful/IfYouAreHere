#include "ResourceManager.h"


ResourceManager::ResourceManager()
{
	mTextures[LIGHT_KITTY_TEXTURE].loadFromFile("..\\..\\..\\res\\lightkitty_all.png");
	mTextures[DARK_KITTY_TEXTURE].loadFromFile("..\\..\\..\\res\\darkkitty_all.png");
	mTextures[SLUG_TEXTURE].loadFromFile("..\\..\\..\\res\\enemy_critter1_st.png");
	mTextures[CIRCLE_TEXTURE].loadFromFile("..\\..\\..\\res\\enemy_circle_all.png");
	mTextures[TRIPLE_TEXTURE].loadFromFile("..\\..\\..\\res\\bigger_enemy_critter3_triple_idle.png");
	mTextures[BULLET_TEXTURE].loadFromFile("..\\..\\..\\res\\bullet.png");
	mTextures[BULLET_LIGHT_1].loadFromFile("..\\..\\..\\res\\lightbullet.png");
	mTextures[BULLET_LIGHT_2].loadFromFile("..\\..\\..\\res\\lightbullet2.png");
	mTextures[BULLET_LIGHT_3].loadFromFile("..\\..\\..\\res\\lightbullet3.png");
	mTextures[BULLET_DARK_1].loadFromFile("..\\..\\..\\res\\darkbullet.png");
	mTextures[BULLET_DARK_2].loadFromFile("..\\..\\..\\res\\darkbullet2.png");
	mTextures[BULLET_DARK_3].loadFromFile("..\\..\\..\\res\\darkbullet3.png");
	mTextures[DROP_TEXTURE].loadFromFile("..\\..\\..\\res\\powerbox.png");
	mTextures[BUTTON_TEXTURE].loadFromFile("..\\..\\..\\res\\superbouton.png");
	mTextures[BUTTON_HOVERED_TEXTURE].loadFromFile("..\\..\\..\\res\\superbouton_hovered.png");
	mTextures[AMALGAMATION_TEXTURE].loadFromFile("..\\..\\..\\res\\critterboss.png");
	mTextures[PARHELION_TEXTURE].loadFromFile("..\\..\\..\\res\\parhelions.png");
	mTextures[PLAY_BUTTON_TEXTURE].loadFromFile("..\\..\\..\\res\\play_button.png");
	mTextures[PLAY_BUTTON_HOVERED_TEXTURE].loadFromFile("..\\..\\..\\res\\play_button_hovered.png");
	mTextures[QUIT_BUTTON_TEXTURE].loadFromFile("..\\..\\..\\res\\quit_button.png");
	mTextures[QUIT_BUTTON_HOVERED_TEXTURE].loadFromFile("..\\..\\..\\res\\quit_button_hovered.png");
	mTextures[LASER_TEXTURE].loadFromFile("..\\..\\..\\res\\laser.png");
	mTextures[MENU_BACKGROUND_TEXTURE].loadFromFile("../../../res/menu_background.png");
	mTextures[DINOCAT_TEXTURE].loadFromFile("../../../res/dinokitties.png");
}

ResourceManager::~ResourceManager()
{
}

sf::Texture* ResourceManager::GetTexture(TextureName texture)
{
	return &mTextures[texture];
}
