#pragma once
#include "Player.h"
#include "PlayerWeapon1Dark.h"
#include "PlayerWeapon2Dark.h"
#include "PlayerWeapon3ADark.h"
#include "PlayerWeapon4ADark.h"
#include "PlayerWeapon3BDark.h"
#include "PlayerWeapon4BDark.h"

#include "PlayerWeapon1Light.h"
#include "PlayerWeapon2Light.h"
#include "PlayerWeapon3ALight.h"
#include "PlayerWeapon3BLight.h"
#include "PlayerWeapon4ALight.h"
#include "PlayerWeapon4BLight.h"

class GameManager;
class SoundManager;

class PlayerController: public Entity
{
	sf::Texture mPlayerTexture;
	sf::Texture mPlayerAlterTexture;

	Player* mPlayer;
	Player* mPlayerAlter;

	Player* mActivePlayer;
	Player* mInactivePlayer;

	bool mDarkWeaponIsA;
	bool mLightWeaponIsA;

	PlayerWeapon1Dark* mPlayerWeapon1Dark;
	PlayerWeapon2Dark* mPlayerWeapon2Dark;
	PlayerWeapon3ADark* mPlayerWeapon3ADark;
	PlayerWeapon3BDark* mPlayerWeapon3BDark;
	PlayerWeapon4ADark* mPlayerWeapon4ADark;
	PlayerWeapon4BDark* mPlayerWeapon4BDark;

	PlayerWeapon1Light* mPlayerWeapon1Light;
	PlayerWeapon2Light* mPlayerWeapon2Light;
	PlayerWeapon3ALight* mPlayerWeapon3ALight;
	PlayerWeapon3BLight* mPlayerWeapon3BLight;
	PlayerWeapon4ALight* mPlayerWeapon4ALight;
	PlayerWeapon4BLight* mPlayerWeapon4BLight;

	GameManager* mGameManager;
	SoundManager* mSoundManager;

	float mSwapTimer = 0.0f;
	float mSwapCooldown = 1.0f;

	float mInvincibilityTimer = 0.0f;
	float mInvincibilityCooldown = 1.5f;

	int mWeaponPower = 0;

	int mLives;

public:
	PlayerController(sf::Texture* pcTexture, GameManager* gm);
	virtual void Update(float deltaTime);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	Player* GetActivePlayerPointer();
	sf::Vector2f GetActivePlayerPosition();
	std::vector<Player*> GetPlayers();
	void ChangeStage();
	void SetLightWeapon(bool lightIsA);
	void SetDarkWeapon(bool darkIsA);
	void IncreaseWeaponPower(int amount);

	bool IsInvincible();
	void SetInvincible();

	void TakeDamage();
	void Reset();
	int GetLives();
	bool DecreaseLife();
	void Swap();
	void SetGameScreen(sf::FloatRect newSize);
	sf::FloatRect GetGameScreen();
};

