#include "Player.h"
#include "PlayerWeapon.h"
#include "PlayerController.h"
#include "Drop.h"
#include <iostream>


Player::Player(sf::Vector2f position, float rotation, TextureName texture, bool isActive, PlayerController* playerController): Character(position, rotation, texture, PLAYERTAG,  true)
{
	mIsCurrent = isActive;

	mSprite.setTextureRect(sf::IntRect(32 * mIsCurrent, 0, 32, 64));
	mSprite.setOrigin(sf::Vector2f(17.0f, 32.0f));
	mSprite.setScale(sf::Vector2f(1.5f, 1.5f));

	mGameScreen = sf::FloatRect(24, 32, 752, 736);

	mHitbox.AddCircle(new sf::CircleShape(5.0f));

	mHitboxDisplay = sf::CircleShape(5.0f);
	mHitboxDisplay.setFillColor(sf::Color(255, 0, 0, 255));
	mHitboxDisplay.setOutlineColor(sf::Color::White);
	mHitboxDisplay.setOutlineThickness(1.0f);
	mHitboxDisplay.setOrigin(5.0f, 5.0f);

	mController = playerController;
}

void Player::Update(float deltaTime)
{
}

void Player::Move(float deltaTime, sf::Vector2f direction)
{
	// You can't leave the box, dinocat.
	sf::Vector2f newPos = deltaTime * mSpeed * direction + getPosition();
	if (newPos.x < mGameScreen.left ||
		newPos.x > mGameScreen.left + mGameScreen.width ||
		newPos.y < mGameScreen.top ||
		newPos.y > mGameScreen.top + mGameScreen.height)
	{
		return;
	}

	move(deltaTime * mSpeed * direction);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);

	if (!mIsCurrent)
	{
		return;
	}

	states.transform.combine(getTransform());
	target.draw(mHitboxDisplay, states);
}

void Player::Shoot(float deltaTime)
{
	// For all weapons, shoot
	for (int i = 0; i < mWeapons.size(); i++)
	{
		mWeapons[i]->Update(deltaTime);
	}
}

void Player::TakeDamage(int damage)
{
	// Call Game manager Lose life
	mController->TakeDamage();
}

void Player::Die()
{
	// Lose.
}

void Player::SetCurrentPlayer(bool activePlayer)
{
	mIsCurrent = activePlayer;
}

void Player::AddWeapon(PlayerWeapon* weapon)
{
	mWeapons.push_back(weapon);
}

void Player::ClearWeapons()
{
	mWeapons.clear();
}

void Player::UpdateTexture(int sprite)
{
	/* "sprite" values :
	* 0 = idle    3 = down
	* 1 = left    4 = up
	* 2 = right
	*/
	mSprite.setTextureRect(sf::IntRect(64 * sprite, 64* not mIsCurrent, 64, 64));
}

void Player::CheckDropCollisions(std::vector<Drop*>* drops)
{
	mHitbox.SetPosition(getPosition());

	for (Drop* drop : *drops)
	{
		if (!drop->IsEntityActive())
		{
			continue;
		}

		if (mHitbox.IsColliding(drop->GetHitboxPointer()))
		{
			// Instead, call an "on hit" method
			drop->OnCollect(this);
			// bullet->SetEntityActive(false);
		}
	}
}

void Player::CollectDrop(int amount)
{
	// Play pickup sound

	mController->IncreaseWeaponPower(amount);
}

void Player::SetFocusSpeed(bool isFocused)
{
	if (isFocused)
	{
		mSpeed = 125.0f;
	}

	else
	{
		mSpeed = 250.0f;
	}
}

void Player::SetGameScreen(sf::FloatRect newSize)
{
	mGameScreen = newSize;
}

sf::FloatRect Player::GetGameScreen()
{
	return mGameScreen;
}
