#include "Menu.h"
#include "MenuButton.h"
#include "GameManager.h"
#include "SceneManager.h"

Menu::Menu(sf::RenderWindow* window, SceneManager* sceneManager): Scene(window)
{
	mButtonHovered = 0;
	mSceneManager = sceneManager;

	menuBgTexture.loadFromFile("../../../res/menu_background.png");
	menuBackground.setTexture(menuBgTexture);
	menuBackground.setScale(sf::Vector2f(2,2));

	mDinocatTexture.loadFromFile("../../../res/dinokitties.png");
	mDinocatSprite.setTexture(mDinocatTexture);
	mDinocatSprite.setScale(sf::Vector2f(2, 2));
	mDinocatSprite.setPosition(sf::Vector2f(75.0f, 70.0f));

	mLightATexture.loadFromFile("../../../res/lightbullet2.png");
	mLightBTexture.loadFromFile("../../../res/lightbullet3.png");
	mDarkATexture.loadFromFile("../../../res/darkbullet2.png");
	mDarkBTexture.loadFromFile("../../../res/darkbullet3.png");

	mLightASprite1.setTexture(mLightATexture);
	mLightASprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightASprite1.setPosition(sf::Vector2f(85.0f, 640.0f));
	mLightASprite1.setRotation(25);

	mLightASprite2.setTexture(mLightATexture);
	mLightASprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightASprite2.setPosition(sf::Vector2f(315.0f, 550.0f));
	mLightASprite2.setRotation(-15);

	mLightBSprite1.setTexture(mLightBTexture);
	mLightBSprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightBSprite1.setPosition(sf::Vector2f(75.0f, 650.0f));

	mLightBSprite2.setTexture(mLightBTexture);
	mLightBSprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightBSprite2.setPosition(sf::Vector2f(325.0f, 550.0f));

	mDarkASprite1.setTexture(mDarkATexture);
	mDarkASprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkASprite1.setPosition(sf::Vector2f(300.0f, 300.0f));

	mDarkASprite2.setTexture(mDarkATexture);
	mDarkASprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkASprite2.setPosition(sf::Vector2f(600.0f, 225.0f));

	mDarkBSprite1.setTexture(mDarkBTexture);
	mDarkBSprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkBSprite1.setPosition(sf::Vector2f(325.0f, 375.0f));
	mDarkBSprite1.setRotation(-155);

	mDarkBSprite2.setTexture(mDarkBTexture);
	mDarkBSprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkBSprite2.setPosition(sf::Vector2f(675.0f, 250.0f));
	mDarkBSprite2.setRotation(125);

	playButtonTexture.loadFromFile("..\\..\\..\\res\\play_button.png");
	playButtonTextureHovered.loadFromFile("..\\..\\..\\res\\play_button_hovered.png");

	quitButtonTexture.loadFromFile("../../../res/quit_button.png");
	quitButtonTextureHovered.loadFromFile("../../../res/quit_button_hovered.png");

	AddButton(new MenuButton(sf::Vector2f(768.0f, 424.0f), 0.0f, sf::Vector2f(180.0f, 80.0f), &playButtonTexture, &playButtonTextureHovered));
	AddButton(new MenuButton(sf::Vector2f(768.0f, 658.0f), 0.0f, sf::Vector2f(180.0f, 80.0f), &quitButtonTexture, &quitButtonTextureHovered));
	mMainMenuButtons[0]->setScale(sf::Vector2f(2, 2));
	mMainMenuButtons[1]->setScale(sf::Vector2f(2, 2));

	mMainMenuButtons[0]->SetHover(true);

	mIsLightA = true;
	mIsDarkA = true;
}

void Menu::Update(float deltaTime)
{
	Scene::Update(deltaTime);

	mTimer += deltaTime;

	mDinocatSprite.setPosition(sf::Vector2f(75.0f, 70.0f + (sinf(mTimer) * 25)));
	mLightASprite1.setPosition(sf::Vector2f(85.0f, 610.0f + (sinf(mTimer - 0.3f) * 25)));
	mLightBSprite1.setPosition(sf::Vector2f(65.0f, 650.0f + (sinf(mTimer - 0.3f) * 25)));
	mLightASprite2.setPosition(sf::Vector2f(325.0f, 550.0f + (sinf(mTimer - 0.3f) * 25)));
	mLightBSprite2.setPosition(sf::Vector2f(325.0f, 550.0f + (sinf(mTimer - 0.3f) * 25)));
	mDarkASprite1.setPosition(sf::Vector2f(300.0f, 300.0f + (sinf(mTimer - 0.3f) * 25)));
	mDarkASprite2.setPosition(sf::Vector2f(600.0f, 225.0f + (sinf(mTimer - 0.3f) * 25)));
	mDarkBSprite1.setPosition(sf::Vector2f(325.0f, 375.0f + (sinf(mTimer - 0.3f) * 25)));
	mDarkBSprite2.setPosition(sf::Vector2f(675.0f, 250.0f + (sinf(mTimer - 0.3f) * 25)));

	mButtonSwapTime -= deltaTime;
	mButtonConfirmTime -= deltaTime;

	if (mButtonSwapTime > 0.0f)
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (mButtonHovered - 1 < 0)
		{
			return;
		}

		mButtonSwapTime = mButtonSwapCooldown;

		mMainMenuButtons[mButtonHovered]->SetHover(false);

		--mButtonHovered;

		mMainMenuButtons[mButtonHovered]->SetHover(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (mButtonHovered + 1 >= 2)
		{
			return;
		}

		mButtonSwapTime = mButtonSwapCooldown;

		mMainMenuButtons[mButtonHovered]->SetHover(false);

		++mButtonHovered;

		mMainMenuButtons[mButtonHovered]->SetHover(true);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (mButtonConfirmTime > 0.0f)
		{
			return;
		}
	
		if (mButtonHovered == 0)
		{
			mSceneManager->GetPlayerController()->Reset();

			mSceneManager->GetPlayerController()->SetLightWeapon(mIsLightA);
			mSceneManager->GetPlayerController()->SetDarkWeapon(mIsDarkA);

			mSceneManager->ChangeToStage(0);
		}

		if (mButtonHovered == 1)
		{
			delete GameManager::GetInstance()->GetSoundManager();

			GameManager::GetInstance()->GetWindow()->close();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
	{
		if (mButtonConfirmTime > 0.0f)
		{
			return;
		}
		mButtonConfirmTime = mButtonConfirmCooldown;
		mIsLightA = !mIsLightA;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		if (mButtonConfirmTime > 0.0f)
		{
			return;
		}
		mButtonConfirmTime = mButtonConfirmCooldown;
		mIsDarkA = !mIsDarkA;
	}
}

void Menu::AddButton(MenuButton* button)
{
	mMainMenuButtons.push_back(button);
	entities.push_back(button);
}

void Menu::EnterScene()
{
	mButtonConfirmTime = mButtonConfirmCooldown;
}

void Menu::ResetScene()
{

}

void Menu::Draw() {

	mCurrentWindow->draw(menuBackground);
	mCurrentWindow->draw(mDinocatSprite);

	if (mIsLightA)
	{
		mCurrentWindow->draw(mLightASprite1);
		mCurrentWindow->draw(mLightASprite2);
	}
	else
	{
		mCurrentWindow->draw(mLightBSprite1);
		mCurrentWindow->draw(mLightBSprite2);
	}

	if (mIsDarkA)
	{
		mCurrentWindow->draw(mDarkASprite1);
		mCurrentWindow->draw(mDarkASprite2);
	}
	else
	{
		mCurrentWindow->draw(mDarkBSprite1);
		mCurrentWindow->draw(mDarkBSprite2);
	}
	Scene::Draw();
}
