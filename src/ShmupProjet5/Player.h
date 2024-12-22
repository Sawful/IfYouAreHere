#pragma once
#include "Character.h"

class PlayerController;
class PlayerWeapon;
class Bullet;
class Drop;

class Player: public Character
{
	bool mIsCurrent;
	std::vector<PlayerWeapon*> mWeapons;
	PlayerController* mController;
	sf::FloatRect mGameScreen;

	sf::CircleShape mHitboxDisplay;

	float mSpeed;
	
	
public:
	Player(sf::Vector2f position, float rotation, sf::Texture* texture, bool isActive, PlayerController* playerController);
	virtual void Update(float deltaTime);
	virtual void Move(float deltaTime, sf::Vector2f direction);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void Shoot(float deltaTime);
	virtual void TakeDamage(int damage);
	virtual void Die();
	void SetCurrentPlayer(bool activePlayer);
	void AddWeapon(PlayerWeapon* weapon);
	void ClearWeapons();
	void UpdateTexture(int sprite = 0);
	void CheckDropCollisions(std::vector<Drop*>* drops);
	void CollectDrop(int amount);
	void SetFocusSpeed(bool isFocused);
	void SetGameScreen(sf::FloatRect newSize);
	sf::FloatRect GetGameScreen();
};

