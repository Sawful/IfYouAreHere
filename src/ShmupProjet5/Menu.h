#pragma once
#include "Scene.h"

class MenuButton;
class SceneManager;

class Menu: public Scene
{
	std::vector<MenuButton*> mMainMenuButtons;
	sf::Texture menuBgTexture;
	sf::Sprite menuBackground;

	sf::Texture mDinocatTexture;
	sf::Sprite mDinocatSprite;

	sf::Texture mLightATexture;
	sf::Sprite mLightASprite1;
	sf::Sprite mLightASprite2;

	sf::Texture mLightBTexture;
	sf::Sprite mLightBSprite1;
	sf::Sprite mLightBSprite2;

	sf::Texture mDarkATexture;
	sf::Sprite mDarkASprite1;
	sf::Sprite mDarkASprite2;

	sf::Texture mDarkBTexture;
	sf::Sprite mDarkBSprite1;
	sf::Sprite mDarkBSprite2;

	bool mIsLightA;
	bool mIsDarkA;

	sf::Texture playButtonTexture;
	sf::Texture playButtonTextureHovered;
	sf::Texture quitButtonTexture;
	sf::Texture quitButtonTextureHovered;

	SceneManager* mSceneManager;

	float mButtonSwapTime = 0.0f;
	float mButtonSwapCooldown = 0.2f;

	float mButtonConfirmTime = 0.0f;
	float mButtonConfirmCooldown = 0.5f;

	float mTimer;

	int mButtonHovered;

public:
	Menu(sf::RenderWindow* window, SceneManager* sceneManager);
	virtual void Update(float deltaTime) override;
	void AddButton(MenuButton* button);
	virtual void EnterScene();
	virtual void ResetScene();
	virtual void Draw() override;
};

