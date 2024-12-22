#include "Menu.h"
#include "MenuButton.h"
#include "GameManager.h"
#include "SceneManager.h"

Menu::Menu(sf::RenderWindow* window, SceneManager* sceneManager): Scene(window)
{
	mButtonHovered = 0;
	mSceneManager = sceneManager;
}

void Menu::Initialize()
{
	ResourceManager* rm = GameManager::GetInstance()->GetResourceManager();

	menuBackground.setTexture(*rm->GetTexture(MENU_BACKGROUND_TEXTURE));
	menuBackground.setScale(sf::Vector2f(2, 2));

	mDinocatSprite.setTexture(*rm->GetTexture(DINOCAT_TEXTURE));
	mDinocatSprite.setScale(sf::Vector2f(2, 2));
	mDinocatSprite.setPosition(sf::Vector2f(75.0f, 70.0f));

	mLightASprite1.setTexture(*rm->GetTexture(BULLET_LIGHT_2));
	mLightASprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightASprite1.setPosition(sf::Vector2f(85.0f, 640.0f));
	mLightASprite1.setRotation(25);

	mLightASprite2.setTexture(*rm->GetTexture(BULLET_LIGHT_2));
	mLightASprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightASprite2.setPosition(sf::Vector2f(315.0f, 550.0f));
	mLightASprite2.setRotation(-15);

	mLightBSprite1.setTexture(*rm->GetTexture(BULLET_LIGHT_3));
	mLightBSprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightBSprite1.setPosition(sf::Vector2f(75.0f, 650.0f));

	mLightBSprite2.setTexture(*rm->GetTexture(BULLET_LIGHT_3));
	mLightBSprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mLightBSprite2.setPosition(sf::Vector2f(325.0f, 550.0f));

	mDarkASprite1.setTexture(*rm->GetTexture(BULLET_DARK_2));
	mDarkASprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkASprite1.setPosition(sf::Vector2f(300.0f, 300.0f));

	mDarkASprite2.setTexture(*rm->GetTexture(BULLET_DARK_2));
	mDarkASprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkASprite2.setPosition(sf::Vector2f(600.0f, 225.0f));

	mDarkBSprite1.setTexture(*rm->GetTexture(BULLET_DARK_3));
	mDarkBSprite1.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkBSprite1.setPosition(sf::Vector2f(325.0f, 375.0f));
	mDarkBSprite1.setRotation(-155);

	mDarkBSprite2.setTexture(*rm->GetTexture(BULLET_DARK_3));
	mDarkBSprite2.setScale(sf::Vector2f(4.0f, 4.0f));
	mDarkBSprite2.setPosition(sf::Vector2f(675.0f, 250.0f));
	mDarkBSprite2.setRotation(125);

	AddButton(new MenuButton(sf::Vector2f(768.0f, 424.0f), 0.0f, sf::Vector2f(180.0f, 80.0f), PLAY_BUTTON_TEXTURE, PLAY_BUTTON_HOVERED_TEXTURE));
	AddButton(new MenuButton(sf::Vector2f(768.0f, 658.0f), 0.0f, sf::Vector2f(180.0f, 80.0f), QUIT_BUTTON_TEXTURE, QUIT_BUTTON_HOVERED_TEXTURE));
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
